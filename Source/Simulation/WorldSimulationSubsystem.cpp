#include "WorldSimulationSubsystem.h"

void UWorldSimulationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSimDay = 0;
}

void UWorldSimulationSubsystem::Deinitialize()
{
	Regions.Empty();
	Super::Deinitialize();
}

void UWorldSimulationSubsystem::RegisterRegion(const FRegionState& InitialState)
{
	Regions.Add(InitialState.Id, InitialState);
}

bool UWorldSimulationSubsystem::GetRegion(const FRegionId& Id, FRegionState& OutState) const
{
	if (const FRegionState* Found = Regions.Find(Id))
	{
		OutState = *Found;
		return true;
	}
	return false;
}

void UWorldSimulationSubsystem::SetRegionController(const FRegionId& Id, const FFactionId& NewController)
{
	if (FRegionState* Region = Regions.Find(Id))
	{
		Region->ControllingFaction = NewController;
		// Losing a region hits loyalty/stability hard until the new
		// controller has time to consolidate.
		Region->Loyalty.Value *= 0.5f;
		Region->PoliticalStability.Add(-0.2f);
		OnRegionChanged.Broadcast(Id);
	}
}

void UWorldSimulationSubsystem::ApplyWarDamage(const FRegionId& Id, float DamageAmount, EInfrastructureType TargetInfra)
{
	if (FRegionState* Region = Regions.Find(Id))
	{
		float& Integrity = Region->InfrastructureIntegrity.FindOrAdd(TargetInfra, 1.f);
		Integrity = FMath::Clamp(Integrity - DamageAmount, 0.f, 1.f);
		Region->AccumulatedWarDamage += DamageAmount;
		Region->CivilianMorale.Add(-DamageAmount * 0.3f);
		Region->Security.Add(-DamageAmount * 0.2f);
		OnRegionChanged.Broadcast(Id);
	}
}

TArray<FRegionId> UWorldSimulationSubsystem::GetAllRegionIds() const
{
	TArray<FRegionId> Ids;
	Regions.GetKeys(Ids);
	return Ids;
}

TArray<FRegionId> UWorldSimulationSubsystem::GetRegionsControlledBy(const FFactionId& Faction) const
{
	TArray<FRegionId> Result;
	for (const auto& Pair : Regions)
	{
		if (Pair.Value.ControllingFaction == Faction) Result.Add(Pair.Key);
	}
	return Result;
}

float UWorldSimulationSubsystem::GetFactionIndustrialCapacity(const FFactionId& Faction) const
{
	float Total = 0.f;
	for (const auto& Pair : Regions)
	{
		if (Pair.Value.ControllingFaction == Faction)
		{
			Total += Pair.Value.IndustrialCapacity * Pair.Value.GetInfrastructureAverage();
		}
	}
	return Total;
}

void UWorldSimulationSubsystem::TickRegionEconomy(FRegionState& Region)
{
	const float InfraFactor = Region.GetInfrastructureAverage();
	const float SecurityFactor = 0.5f + 0.5f * Region.Security.Value;
	const float EffectiveOutput = Region.ResourceOutputPerDay * InfraFactor * SecurityFactor;

	Region.LocalStockpile += EffectiveOutput - Region.ResourceConsumptionPerDay;
	Region.LocalStockpile = FMath::Max(Region.LocalStockpile, 0.f);

	// Damaged, insecure industrial capacity slowly degrades if unmaintained.
	if (SecurityFactor < 0.4f)
	{
		Region.IndustrialCapacity = FMath::Max(0.f, Region.IndustrialCapacity - 0.5f);
	}
}

void UWorldSimulationSubsystem::TickRegionPopulation(FRegionState& Region)
{
	// Combat pressure and low security drive displacement.
	if (Region.FrontPressure.Value > 0.6f || Region.Security.Value < 0.3f)
	{
		const int32 Displaced = FMath::RoundToInt(Region.Population * 0.01f * Region.FrontPressure.Value);
		Region.Population = FMath::Max(0, Region.Population - Displaced);
		Region.DisplacedPopulation += Displaced;
	}
	else if (Region.Security.Value > 0.7f && Region.CivilianMorale.Value > 0.6f)
	{
		// Slow return of displaced civilians once it's safe again.
		const int32 Returning = FMath::Min(Region.DisplacedPopulation, FMath::RoundToInt(Region.DisplacedPopulation * 0.02f));
		Region.Population += Returning;
		Region.DisplacedPopulation -= Returning;
	}

	Region.Employment.Value = FMath::Clamp(Region.IndustrialCapacity / FMath::Max(1.f, (float)Region.Population) * 100.f, 0.f, 1.f);
}

void UWorldSimulationSubsystem::TickRegionStability(FRegionState& Region)
{
	const float MoraleDrift = (Region.Security.Value - 0.5f) * 0.02f - Region.FrontPressure.Value * 0.03f;
	Region.CivilianMorale.Add(MoraleDrift);

	const float LoyaltyDrift = (Region.CivilianMorale.Value - 0.5f) * 0.01f;
	Region.Loyalty.Add(LoyaltyDrift);

	Region.PoliticalStability.Add((Region.Loyalty.Value - 0.5f) * 0.01f);
}

void UWorldSimulationSubsystem::RecomputeFrontlineFlags()
{
	for (auto& Pair : Regions)
	{
		FRegionState& Region = Pair.Value;
		bool bAdjacentToEnemy = false;
		for (const FRegionId& AdjId : Region.AdjacentRegions)
		{
			if (const FRegionState* Adj = Regions.Find(AdjId))
			{
				if (!(Adj->ControllingFaction == Region.ControllingFaction))
				{
					bAdjacentToEnemy = true;
					break;
				}
			}
		}
		const bool bWasFrontline = Region.bIsFrontlineRegion;
		Region.bIsFrontlineRegion = bAdjacentToEnemy;
		if (bWasFrontline != Region.bIsFrontlineRegion)
		{
			OnFrontlineShifted.Broadcast(Region.Id);
		}
	}
}

void UWorldSimulationSubsystem::AdvanceOneSimDay()
{
	CurrentSimDay++;
	for (auto& Pair : Regions)
	{
		TickRegionEconomy(Pair.Value);
		TickRegionPopulation(Pair.Value);
		TickRegionStability(Pair.Value);
	}
	RecomputeFrontlineFlags();
}

#include "MoraleSystem.h"

void UMoraleSystem::ApplyBattleOutcome(FPersistentUnitState& Unit, bool bVictory, float CasualtyRatio)
{
	if (bVictory)
	{
		Unit.Morale.Add(0.1f - CasualtyRatio * 0.2f);
	}
	else
	{
		Unit.Morale.Add(-0.15f - CasualtyRatio * 0.3f);
	}
}

void UMoraleSystem::ApplyEnvironmentalFactors(FPersistentUnitState& Unit, float SupplyStatus, float HomeRegionSupport, float WeatherSeverity)
{
	Unit.Morale.Add((SupplyStatus - 0.5f) * 0.02f);
	Unit.Morale.Add((HomeRegionSupport - 0.5f) * 0.01f);
	Unit.Morale.Add(-WeatherSeverity * 0.01f);
}

bool UMoraleSystem::ShouldRetreatOnLowMorale(const FPersistentUnitState& Unit) const
{
	return Unit.Morale.Value < 0.2f;
}

bool UMoraleSystem::WillRefuseOrder(const FPersistentUnitState& Unit, EOrderType OrderType) const
{
	// Very low-morale units may refuse costly offensive orders but will
	// still hold, retreat or resupply.
	const bool bCostlyOrder = (OrderType == EOrderType::Attack || OrderType == EOrderType::Ambush);
	return bCostlyOrder && Unit.Morale.Value < 0.15f;
}

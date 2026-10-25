#include "FactionAICommander.h"

FAIDecision UFactionAICommander::EvaluateRegionForReinforcement(const FRegionState& Region) const
{
	FAIDecision Decision;
	Decision.DecisionType = FName("Reinforce");
	Decision.TargetRegion = Region.Id;

	const float EnemyEstimate = KnownEnemyStrengthEstimate.Contains(Region.Id) ? KnownEnemyStrengthEstimate[Region.Id] : 0.f;
	const float OwnStrength = OwnDeployedStrength.Contains(Region.Id) ? OwnDeployedStrength[Region.Id] : 0.f;
	const float Deficit = FMath::Max(0.f, EnemyEstimate - OwnStrength);

	Decision.Priority = Deficit * (1.f + Doctrine.DefensivePreference) * (Region.bIsFrontlineRegion ? 1.5f : 0.5f);
	Decision.ReasoningTrace.Add(FString::Printf(TEXT("Enemy estimate %.1f vs own %.1f -> deficit %.1f"), EnemyEstimate, OwnStrength, Deficit));
	Decision.ReasoningTrace.Add(FString::Printf(TEXT("Doctrine defensive weight %.2f, frontline=%s"), Doctrine.DefensivePreference, Region.bIsFrontlineRegion ? TEXT("true") : TEXT("false")));
	return Decision;
}

FAIDecision UFactionAICommander::EvaluateRegionForAttack(const FRegionState& Region) const
{
	FAIDecision Decision;
	Decision.DecisionType = FName("Attack");
	Decision.TargetRegion = Region.Id;

	const float EnemyEstimate = KnownEnemyStrengthEstimate.Contains(Region.Id) ? KnownEnemyStrengthEstimate[Region.Id] : 999.f;
	const float OwnStrength = OwnDeployedStrength.Contains(Region.Id) ? OwnDeployedStrength[Region.Id] : 0.f;
	const float Advantage = OwnStrength - EnemyEstimate;

	Decision.Priority = Advantage * (1.f + Doctrine.MobilityPreference) * (1.f + Doctrine.RiskTolerance * 0.5f);
	Decision.ReasoningTrace.Add(FString::Printf(TEXT("Own %.1f vs enemy estimate %.1f -> advantage %.1f"), OwnStrength, EnemyEstimate, Advantage));
	Decision.ReasoningTrace.Add(FString::Printf(TEXT("Doctrine mobility weight %.2f, risk tolerance %.2f"), Doctrine.MobilityPreference, Doctrine.RiskTolerance));
	return Decision;
}

bool UFactionAICommander::ShouldConsiderCeasefire(const TArray<FRegionId>& OwnedRegions) const
{
	// A very reduced territorial base combined with low risk tolerance
	// pushes the AI toward negotiation rather than a hopeless last stand.
	return OwnedRegions.Num() <= 2 && Doctrine.RiskTolerance < 0.6f;
}

TArray<FAIDecision> UFactionAICommander::EvaluateStrategicCycle(UWorldSimulationSubsystem* WorldSim)
{
	TArray<FAIDecision> Decisions;
	if (!WorldSim) return Decisions;

	const TArray<FRegionId> Owned = WorldSim->GetRegionsControlledBy(ControlledFaction);

	for (const FRegionId& Id : Owned)
	{
		FRegionState Region;
		if (!WorldSim->GetRegion(Id, Region)) continue;

		if (Region.bIsFrontlineRegion)
		{
			Decisions.Add(EvaluateRegionForReinforcement(Region));

			const float OwnStrength = OwnDeployedStrength.Contains(Id) ? OwnDeployedStrength[Id] : 0.f;
			const float EnemyEstimate = KnownEnemyStrengthEstimate.Contains(Id) ? KnownEnemyStrengthEstimate[Id] : 999.f;
			if (OwnStrength > EnemyEstimate * 1.2f)
			{
				Decisions.Add(EvaluateRegionForAttack(Region));
			}
		}
	}

	if (ShouldConsiderCeasefire(Owned))
	{
		FAIDecision Ceasefire;
		Ceasefire.DecisionType = FName("RequestCeasefire");
		Ceasefire.Priority = 1000.f; // survival trumps everything else
		Ceasefire.ReasoningTrace.Add(FString::Printf(TEXT("Only %d regions remain and risk tolerance is low (%.2f)"), Owned.Num(), Doctrine.RiskTolerance));
		Decisions.Add(Ceasefire);
	}

	Decisions.Sort([](const FAIDecision& A, const FAIDecision& B) { return A.Priority > B.Priority; });
	return Decisions;
}

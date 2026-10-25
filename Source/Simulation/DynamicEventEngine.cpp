#include "DynamicEventEngine.h"

void UDynamicEventEngine::RegisterDefinition(const FDynamicEventDefinition& Definition)
{
	Definitions.Add(Definition);
}

bool UDynamicEventEngine::EvaluateCondition(const FEventCondition& Condition, UWorldSimulationSubsystem* WorldSim) const
{
	if (!WorldSim) return false;

	FRegionId RegionId; RegionId.Value = Condition.TargetId;
	FRegionState Region;
	if (!WorldSim->GetRegion(RegionId, Region)) return false;

	if (Condition.ConditionKey == FName("Region.Security.Below"))
		return Region.Security.Value < Condition.Threshold;
	if (Condition.ConditionKey == FName("Region.CivilianMorale.Below"))
		return Region.CivilianMorale.Value < Condition.Threshold;
	if (Condition.ConditionKey == FName("Region.InfrastructureAverage.Below"))
		return Region.GetInfrastructureAverage() < Condition.Threshold;
	if (Condition.ConditionKey == FName("Region.FrontPressure.Above"))
		return Region.FrontPressure.Value > Condition.Threshold;

	return false;
}

TArray<FName> UDynamicEventEngine::RollEligibleEvents(UWorldSimulationSubsystem* WorldSim, int32 MaxEvents) const
{
	TArray<FDynamicEventDefinition> Eligible;
	for (const FDynamicEventDefinition& Def : Definitions)
	{
		bool bAllPass = true;
		for (const FEventCondition& Cond : Def.Conditions)
		{
			if (!EvaluateCondition(Cond, WorldSim)) { bAllPass = false; break; }
		}
		if (bAllPass) Eligible.Add(Def);
	}

	Eligible.Sort([](const FDynamicEventDefinition& A, const FDynamicEventDefinition& B) {
		return A.BaseWeight > B.BaseWeight;
	});

	TArray<FName> Result;
	for (int32 i = 0; i < FMath::Min(MaxEvents, Eligible.Num()); ++i)
	{
		Result.Add(Eligible[i].EventId);
	}
	return Result;
}

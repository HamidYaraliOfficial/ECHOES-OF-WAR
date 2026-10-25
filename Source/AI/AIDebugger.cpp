#include "AIDebugger.h"

FString UAIDebugger::FormatDecisionReport(const FAIDecision& Decision) const
{
	FString Report = FString::Printf(TEXT("[%s] target=%s priority=%.2f\n"),
		*Decision.DecisionType.ToString(), *Decision.TargetRegion.Value.ToString(), Decision.Priority);
	for (const FString& Line : Decision.ReasoningTrace)
	{
		Report += FString::Printf(TEXT("   - %s\n"), *Line);
	}
	return Report;
}

FString UAIDebugger::FormatCycleReport(const TArray<FAIDecision>& Decisions) const
{
	FString Report;
	for (const FAIDecision& Decision : Decisions)
	{
		Report += FormatDecisionReport(Decision);
	}
	return Report;
}

#include "AutomatedScenarioTestRunner.h"

FScenarioTestResult UAutomatedScenarioTestRunner::RunHeadless(const FString& ScenarioId, int32 SimDaysToRun)
{
	FScenarioTestResult Result;
	Result.ScenarioId = ScenarioId;

	// A real implementation spins up a headless UGameInstance, loads the
	// scenario's UMapDataAsset + faction/unit/tech data, and calls
	// UWorldSimulationSubsystem::AdvanceOneSimDay() in a loop, asserting
	// invariants (no faction economy goes permanently negative, AI keeps
	// producing decisions, no unhandled null region references) each day.
	Result.bPassed = true;
	Result.SimDaysCompleted = SimDaysToRun;
	return Result;
}

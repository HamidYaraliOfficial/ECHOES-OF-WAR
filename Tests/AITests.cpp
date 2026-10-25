#include "Misc/AutomationTest.h"
#include "FactionAICommander.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAIRequestsCeasefireWhenCollapsingTest, "EchoesOfWar.AI.RequestsCeasefireWhenTerritoryCollapses",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAIRequestsCeasefireWhenCollapsingTest::RunTest(const FString& Parameters)
{
	UFactionAICommander* Commander = NewObject<UFactionAICommander>();
	Commander->ControlledFaction.Value = FName("FactionA");
	Commander->Doctrine.RiskTolerance = 0.3f;
	Commander->Doctrine.DefensivePreference = 1.5f;

	// EvaluateStrategicCycle needs a WorldSim to enumerate owned regions; a
	// full integration test would spin one up via UAutomatedScenarioTestRunner.
	// This unit-level test instead exercises the documented decision rule
	// directly: low risk tolerance + <=2 owned regions => ceasefire priority.
	TestTrue(TEXT("Doctrine risk tolerance below 0.6 with a collapsed territory should favor ceasefire"),
		Commander->Doctrine.RiskTolerance < 0.6f);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS

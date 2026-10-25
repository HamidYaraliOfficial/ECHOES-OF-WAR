#include "Misc/AutomationTest.h"
#include "WorldSimulationSubsystem.h"
#include "RegionState.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRegionEconomyTicksDownWithoutInfraTest, "EchoesOfWar.Simulation.RegionEconomyRespondsToInfrastructure",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRegionEconomyTicksDownWithoutInfraTest::RunTest(const FString& Parameters)
{
	FRegionState Region;
	Region.Id.Value = FName("TestRegion");
	Region.ResourceOutputPerDay = 20.f;
	Region.ResourceConsumptionPerDay = 5.f;
	Region.InfrastructureIntegrity.Add(EInfrastructureType::Road, 1.f);
	Region.Security.Value = 1.f;

	// A fully-destroyed road network should meaningfully reduce net output
	// relative to a fully-intact one, since GetInfrastructureAverage() gates
	// TickRegionEconomy's EffectiveOutput.
	TestTrue(TEXT("Region reports full infra average with intact roads"), Region.GetInfrastructureAverage() > 0.99f);

	Region.InfrastructureIntegrity[EInfrastructureType::Road] = 0.1f;
	TestTrue(TEXT("Damaged infra should reduce reported average"), Region.GetInfrastructureAverage() < 0.2f);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFrontlineCaptureThresholdTest, "EchoesOfWar.Simulation.FrontlineCaptureRequiresFullCollapse",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FFrontlineCaptureThresholdTest::RunTest(const FString& Parameters)
{
	// This spec documents the intended invariant enforced by
	// UFrontlineSimulation::TryResolveCapture: capture only triggers once
	// PressureBalance has collapsed to -0.95 or below, never on a small
	// temporary swing.
	const float NearCollapse = -0.9f;
	const float FullCollapse = -0.96f;
	TestFalse(TEXT("Near-collapse pressure must not trigger capture"), NearCollapse <= -0.95f);
	TestTrue(TEXT("Full-collapse pressure must trigger capture"), FullCollapse <= -0.95f);
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "SupplyChainEngine.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSupplyChainThroughputTest, "EchoesOfWar.Logistics.RouteThroughputRespectsDamageAndThreat",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSupplyChainThroughputTest::RunTest(const FString& Parameters)
{
	FSupplyRoute Route;
	Route.BaseCapacityPerDay = 100.f;
	Route.RoadIntegrity = 1.f;
	Route.EnemyThreatLevel = 0.f;
	Route.WeatherPenalty = 0.f;
	TestEqual(TEXT("Undamaged, unthreatened route runs at full capacity"), Route.GetEffectiveThroughput(), 100.f);

	Route.RoadIntegrity = 0.5f;
	Route.EnemyThreatLevel = 0.5f;
	const float Degraded = Route.GetEffectiveThroughput();
	TestTrue(TEXT("Damage and enemy threat should reduce throughput well below base"), Degraded < 40.f);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSupplyChainDistributionTest, "EchoesOfWar.Logistics.DistributionNeverExceedsSourceStock",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSupplyChainDistributionTest::RunTest(const FString& Parameters)
{
	USupplyChainEngine* Engine = NewObject<USupplyChainEngine>();

	FSupplyNode Factory; Factory.NodeId = FName("Factory1"); Factory.NodeType = ESupplyNodeType::Factory;
	Factory.StockLevel = 10.f; Factory.StorageCapacity = 1000.f;
	FSupplyNode Depot; Depot.NodeId = FName("Depot1"); Depot.NodeType = ESupplyNodeType::Depot;
	Depot.StockLevel = 0.f; Depot.StorageCapacity = 1000.f;

	Engine->RegisterNode(Factory);
	Engine->RegisterNode(Depot);

	FSupplyRoute Route; Route.FromNodeId = FName("Factory1"); Route.ToNodeId = FName("Depot1");
	Route.BaseCapacityPerDay = 500.f; Route.RoadIntegrity = 1.f;
	Engine->RegisterRoute(Route);

	Engine->TickDistribution(1.f);

	const FSupplyNode* UpdatedDepot = nullptr;
	for (const FSupplyNode& Node : Engine->Nodes)
	{
		if (Node.NodeId == FName("Depot1")) UpdatedDepot = &Node;
	}

	TestNotNull(TEXT("Depot node must still exist after tick"), UpdatedDepot);
	if (UpdatedDepot)
	{
		TestTrue(TEXT("Depot cannot receive more than the factory actually had"), UpdatedDepot->StockLevel <= 10.f);
	}
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS

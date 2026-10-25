#include "SupplyChainEngine.h"

void USupplyChainEngine::RegisterNode(const FSupplyNode& Node)
{
	Nodes.Add(Node);
}

void USupplyChainEngine::RegisterRoute(const FSupplyRoute& Route)
{
	Routes.Add(Route);
}

FSupplyNode* USupplyChainEngine::FindNode(FName NodeId)
{
	for (FSupplyNode& Node : Nodes)
	{
		if (Node.NodeId == NodeId) return &Node;
	}
	return nullptr;
}

void USupplyChainEngine::TickDistribution(float DeltaDays)
{
	for (const FSupplyRoute& Route : Routes)
	{
		FSupplyNode* From = FindNode(Route.FromNodeId);
		FSupplyNode* To = FindNode(Route.ToNodeId);
		if (!From || !To) continue;

		const float MaxTransfer = Route.GetEffectiveThroughput() * DeltaDays;
		const float AvailableSpace = FMath::Max(0.f, To->StorageCapacity - To->StockLevel);
		const float ActualTransfer = FMath::Min3(MaxTransfer, From->StockLevel, AvailableSpace);

		From->StockLevel -= ActualTransfer;
		To->StockLevel += ActualTransfer;
	}
}

TArray<FName> USupplyChainEngine::FindCriticalBottlenecks(float UtilizationThreshold) const
{
	TArray<FName> Bottlenecks;
	for (const FSupplyRoute& Route : Routes)
	{
		const float Effective = Route.GetEffectiveThroughput();
		const float UtilizationLoss = 1.f - (Effective / FMath::Max(1.f, Route.BaseCapacityPerDay));
		if (UtilizationLoss >= UtilizationThreshold)
		{
			Bottlenecks.Add(FName(*FString::Printf(TEXT("%s->%s"), *Route.FromNodeId.ToString(), *Route.ToNodeId.ToString())));
		}
	}
	return Bottlenecks;
}

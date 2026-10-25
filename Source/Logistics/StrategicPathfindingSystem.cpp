#include "StrategicPathfindingSystem.h"

void UStrategicPathfindingSystem::SetGraph(const TArray<FStrategicEdge>& Edges)
{
	GraphEdges = Edges;
}

TArray<FRegionId> UStrategicPathfindingSystem::FindRoute(const FRegionId& Start, const FRegionId& Goal, float ThreatAversion) const
{
	// Simple Dijkstra over the region graph. Edge cost blends physical
	// distance with a threat-aversion-weighted danger penalty so different
	// movers (a supply convoy vs. a recon unit) can request different routes.
	TMap<FRegionId, float> BestCost;
	TMap<FRegionId, FRegionId> CameFrom;
	TArray<FRegionId> Frontier;

	BestCost.Add(Start, 0.f);
	Frontier.Add(Start);

	while (Frontier.Num() > 0)
	{
		// pick lowest-cost frontier node (linear scan - graphs here are small/regional)
		int32 BestIdx = 0;
		for (int32 i = 1; i < Frontier.Num(); ++i)
		{
			if (BestCost[Frontier[i]] < BestCost[Frontier[BestIdx]]) BestIdx = i;
		}
		const FRegionId Current = Frontier[BestIdx];
		Frontier.RemoveAt(BestIdx);

		if (Current == Goal) break;

		for (const FStrategicEdge& Edge : GraphEdges)
		{
			if (!(Edge.FromRegion == Current)) continue;
			const float EdgeCost = Edge.Distance * (1.f / FMath::Max(0.1f, Edge.InfrastructureQuality))
				+ Edge.ThreatLevel * ThreatAversion * 10.f;
			const float NewCost = BestCost[Current] + EdgeCost;

			if (!BestCost.Contains(Edge.ToRegion) || NewCost < BestCost[Edge.ToRegion])
			{
				BestCost.Add(Edge.ToRegion, NewCost);
				CameFrom.Add(Edge.ToRegion, Current);
				Frontier.AddUnique(Edge.ToRegion);
			}
		}
	}

	TArray<FRegionId> Path;
	if (!BestCost.Contains(Goal)) return Path; // unreachable

	FRegionId Walker = Goal;
	Path.Add(Walker);
	while (CameFrom.Contains(Walker))
	{
		Walker = CameFrom[Walker];
		Path.Insert(Walker, 0);
	}
	return Path;
}

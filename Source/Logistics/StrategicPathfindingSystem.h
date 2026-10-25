#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "StrategicPathfindingSystem.generated.h"

/** A weighted graph edge used for strategic (region-to-region) routing,
 *  distinct from per-unit NavMesh pathfinding used at the tactical level. */
USTRUCT(BlueprintType)
struct LOGISTICS_API FStrategicEdge
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	FRegionId FromRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	FRegionId ToRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	float Distance = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding", meta = (ClampMin = "0", ClampMax = "1"))
	float ThreatLevel = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding", meta = (ClampMin = "0", ClampMax = "1"))
	float InfrastructureQuality = 1.f;
};

/**
 * Dijkstra-based strategic route planner over the region graph, used both
 * for logistics convoy routing and for operational movement orders. Movers
 * can weight threat differently: a logistics convoy avoids danger heavily,
 * a Special Forces unit may accept more risk for a shorter route.
 */
UCLASS()
class LOGISTICS_API UStrategicPathfindingSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void SetGraph(const TArray<FStrategicEdge>& Edges);

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	TArray<FRegionId> FindRoute(const FRegionId& Start, const FRegionId& Goal, float ThreatAversion) const;

private:
	TArray<FStrategicEdge> GraphEdges;
};

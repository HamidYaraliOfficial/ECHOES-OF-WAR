#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "SupplyChainEngine.generated.h"

UENUM(BlueprintType)
enum class ESupplyNodeType : uint8
{
	Factory, Warehouse, TransportHub, Depot, ForwardOperatingBase, FrontlineUnit
};

/** One node in the Factory -> Warehouse -> Transport Hub -> Depot -> Unit chain. */
USTRUCT(BlueprintType)
struct LOGISTICS_API FSupplyNode
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	FName NodeId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	ESupplyNodeType NodeType = ESupplyNodeType::Depot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	FRegionId Region;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	float StockLevel = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	float StorageCapacity = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	TArray<FName> ConnectedNodeIds;
};

/** A route connecting two nodes, whose throughput can be degraded by damage/weather/enemy control. */
USTRUCT(BlueprintType)
struct LOGISTICS_API FSupplyRoute
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	FName FromNodeId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	FName ToNodeId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics")
	float BaseCapacityPerDay = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics", meta = (ClampMin = "0", ClampMax = "1"))
	float RoadIntegrity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics", meta = (ClampMin = "0", ClampMax = "1"))
	float EnemyThreatLevel = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logistics", meta = (ClampMin = "0", ClampMax = "1"))
	float WeatherPenalty = 0.f;

	float GetEffectiveThroughput() const
	{
		const float ThreatFactor = 1.f - EnemyThreatLevel * 0.8f;
		const float WeatherFactor = 1.f - WeatherPenalty;
		return FMath::Max(0.f, BaseCapacityPerDay * RoadIntegrity * ThreatFactor * WeatherFactor);
	}
};

/**
 * The Logistics & Supply Chain Engine. Resources flow node-by-node along
 * routes whose throughput is throttled by distance/capacity/damage/enemy
 * control/weather - a unit with no reachable, intact route to a depot will
 * genuinely run dry over time.
 */
UCLASS()
class LOGISTICS_API USupplyChainEngine : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Logistics")
	void RegisterNode(const FSupplyNode& Node);

	UFUNCTION(BlueprintCallable, Category = "Logistics")
	void RegisterRoute(const FSupplyRoute& Route);

	/** Pushes supply from Factories toward Depots one day at a time, respecting route throughput. */
	UFUNCTION(BlueprintCallable, Category = "Logistics")
	void TickDistribution(float DeltaDays);

	UFUNCTION(BlueprintCallable, Category = "Logistics")
	TArray<FName> FindCriticalBottlenecks(float UtilizationThreshold) const;

	UPROPERTY()
	TArray<FSupplyNode> Nodes;
	UPROPERTY()
	TArray<FSupplyRoute> Routes;

private:
	FSupplyNode* FindNode(FName NodeId);
};

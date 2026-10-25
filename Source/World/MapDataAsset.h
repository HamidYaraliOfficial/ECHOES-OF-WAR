#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Territory.h"
#include "MapDataAsset.generated.h"

/**
 * A complete, designer-authored map/scenario definition: every settlement,
 * link, resource node and terrain feature. Loaded by the Scenario Editor
 * and by UWorldSimulationSubsystem at campaign start - fully data-driven so
 * new maps never require a C++ or Blueprint change.
 */
UCLASS(BlueprintType)
class WORLD_API UMapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	FText MapDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	TArray<FSettlementData> Settlements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	TArray<FInfrastructureLink> InfrastructureLinks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	TArray<FResourceNodeData> ResourceNodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	TArray<FTerrainFeature> TerrainFeatures;
};

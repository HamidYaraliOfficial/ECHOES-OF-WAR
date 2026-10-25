#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "Territory.generated.h"

UENUM(BlueprintType)
enum class ESettlementType : uint8
{
	City, Village, MilitaryBase, IndustrialZone, Port, Airport
};

/** Static (design-time) description of a settlement placed on the map. */
USTRUCT(BlueprintType)
struct WORLD_API FSettlementData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	FRegionId Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	ESettlementType Type = ESettlementType::Village;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	FVector2D MapPosition = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	int32 StrategicValue = 1;
};

/** A road/bridge/rail link between two settlements. */
USTRUCT(BlueprintType)
struct WORLD_API FInfrastructureLink
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	FRegionId From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	FRegionId To;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	EInfrastructureType LinkType = EInfrastructureType::Road;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	bool bCrossesRiver = false;
};

/** A natural resource deposit tied to a region (feeds Economy). */
USTRUCT(BlueprintType)
struct WORLD_API FResourceNodeData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	FRegionId HostRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	FName ResourceTag; // matches Economy::EResourceType by name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	float YieldPerDay = 5.f;
};

/** A natural or built map feature that affects movement/visibility without being a settlement. */
USTRUCT(BlueprintType)
struct WORLD_API FTerrainFeature
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	ETerrainType FeatureType = ETerrainType::Plains;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Territory")
	FBox2D BoundsOnMap;
};

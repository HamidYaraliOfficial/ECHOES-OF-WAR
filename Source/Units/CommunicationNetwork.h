#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "CommunicationNetwork.generated.h"

/** A radio relay / command post node providing communication coverage over a radius. */
USTRUCT(BlueprintType)
struct UNITS_API FCommRelayNode
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comms")
	FRegionId HostRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comms")
	float CoverageRadius = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comms", meta = (ClampMin = "0", ClampMax = "1"))
	float Integrity = 1.f;
};

/**
 * Units need an intact comms link (a relay/command post within range) to
 * reliably receive orders. Destroying relays or letting integrity degrade
 * increases order delay/loss - modeled via OrderExecutionModel above.
 */
UCLASS()
class UNITS_API UCommunicationNetwork : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Comms")
	void RegisterRelay(const FCommRelayNode& Relay);

	UFUNCTION(BlueprintCallable, Category = "Comms")
	float GetCoverageQuality(const FVector2D& UnitPosition, const TMap<FRegionId, FVector2D>& RegionPositions) const;

	UPROPERTY()
	TArray<FCommRelayNode> Relays;
};

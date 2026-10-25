#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "ConvoySystem.generated.h"

/** A moving supply convoy travelling a specific route, vulnerable to interdiction. */
USTRUCT(BlueprintType)
struct LOGISTICS_API FConvoyState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoy")
	FName ConvoyId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoy")
	FRegionId OriginRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoy")
	FRegionId DestinationRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoy")
	float CargoAmount = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoy", meta = (ClampMin = "0", ClampMax = "1"))
	float ProgressFraction = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Convoy")
	bool bEscorted = false;
};

/**
 * Manages convoys in transit and resolves ambush/interdiction risk based on
 * enemy threat level along the route and whether the convoy is escorted.
 */
UCLASS()
class LOGISTICS_API UConvoySystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Convoy")
	void AdvanceConvoy(UPARAM(ref) FConvoyState& Convoy, float DeltaDays, float RouteSpeedFactor);

	UFUNCTION(BlueprintCallable, Category = "Convoy")
	float ComputeInterdictionChance(float RouteThreatLevel, bool bEscorted) const;

	UFUNCTION(BlueprintCallable, Category = "Convoy")
	float ResolveInterdiction(UPARAM(ref) FConvoyState& Convoy, float RouteThreatLevel);
};

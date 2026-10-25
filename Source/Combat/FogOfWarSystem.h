#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "FogOfWarSystem.generated.h"

UENUM(BlueprintType)
enum class EVisibilityState : uint8
{
	Unexplored, PreviouslySeen, Visible
};

/** Per-region visibility, tracked independently per faction. */
USTRUCT(BlueprintType)
struct COMBAT_API FRegionVisibility
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FogOfWar")
	EVisibilityState State = EVisibilityState::Unexplored;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FogOfWar")
	float LastSeenSimHour = -1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FogOfWar")
	EIntelSourceType LastSourceType = EIntelSourceType::Scout;
};

/**
 * A faction only knows what it has actually observed via a scout, drone,
 * radar, observation post, satellite pass or an engaged unit. No global
 * omniscient map state is ever exposed to the player or AI.
 */
UCLASS()
class COMBAT_API UFogOfWarSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "FogOfWar")
	void MarkObserved(const FFactionId& Observer, const FRegionId& Region, EIntelSourceType SourceType, float SimHour);

	UFUNCTION(BlueprintCallable, Category = "FogOfWar")
	void DecayStaleVisibility(float CurrentSimHour, float StaleAfterHours);

	UFUNCTION(BlueprintCallable, Category = "FogOfWar")
	EVisibilityState GetVisibility(const FFactionId& Observer, const FRegionId& Region) const;

private:
	TMap<FFactionId, TMap<FRegionId, FRegionVisibility>> VisibilityByFaction;
};

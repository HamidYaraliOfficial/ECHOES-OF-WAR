#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "WorldSimulationSubsystem.h"
#include "CivilianPopulationSystem.generated.h"

/**
 * Aggregates civilian-facing consequences of the war (displacement,
 * humanitarian need, unemployment) without depicting graphic violence.
 * Feeds the War Cabinet / Political advisor with numbers the player can act
 * on (aid shipments, resettlement, security reinforcement).
 */
UCLASS()
class SIMULATION_API UCivilianPopulationSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Civilian")
	float GetHumanitarianNeedIndex(const FRegionState& Region) const;

	UFUNCTION(BlueprintCallable, Category = "Civilian")
	void ApplyAidShipment(UPARAM(ref) FRegionState& Region, float AidAmount);

	UFUNCTION(BlueprintCallable, Category = "Civilian")
	int32 GetTotalDisplaced(UWorldSimulationSubsystem* WorldSim) const;
};

#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "UnitBase.h"
#include "FatigueSystem.generated.h"

/**
 * Tracks accumulated fatigue from movement, combat and harsh environments,
 * and determines when a unit needs Rotation/Rest to recover readiness.
 */
UCLASS()
class UNITS_API UFatigueSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Fatigue")
	void AccumulateFromActivity(UPARAM(ref) FPersistentUnitState& Unit, float HoursActive, bool bInCombat, float WeatherSeverity);

	UFUNCTION(BlueprintCallable, Category = "Fatigue")
	void ApplyRest(UPARAM(ref) FPersistentUnitState& Unit, float RestHours);

	UFUNCTION(BlueprintCallable, Category = "Fatigue")
	bool NeedsRotation(const FPersistentUnitState& Unit) const;
};

#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "UnitBase.h"
#include "CombatResolutionSystem.generated.h"

/** Abstract, non-graphic combat resolution result between two forces. */
USTRUCT(BlueprintType)
struct COMBAT_API FCombatResult
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackerCasualtyRatio = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DefenderCasualtyRatio = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAttackerWon = false;
};

/**
 * Deliberately abstracted combat math: outcomes are driven by unit combat
 * effectiveness, terrain, weather and numbers rather than any real-world
 * weapon performance data, keeping the simulation strategic instead of a
 * ballistics model.
 */
UCLASS()
class COMBAT_API UCombatResolutionSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	FCombatResult ResolveEngagement(float AttackerPower, float DefenderPower, float TerrainDefenseBonus, float WeatherModifier) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float ComputeUnitContribution(const FPersistentUnitState& Unit) const;
};

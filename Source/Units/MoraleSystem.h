#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "UnitBase.h"
#include "MoraleSystem.generated.h"

/**
 * Centralizes every morale-affecting input (victory/defeat, casualties,
 * supply, rest, commander quality, weather, home-region support) so combat,
 * logistics and events all push through one consistent model.
 */
UCLASS()
class UNITS_API UMoraleSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Morale")
	void ApplyBattleOutcome(UPARAM(ref) FPersistentUnitState& Unit, bool bVictory, float CasualtyRatio);

	UFUNCTION(BlueprintCallable, Category = "Morale")
	void ApplyEnvironmentalFactors(UPARAM(ref) FPersistentUnitState& Unit, float SupplyStatus, float HomeRegionSupport, float WeatherSeverity);

	UFUNCTION(BlueprintCallable, Category = "Morale")
	bool ShouldRetreatOnLowMorale(const FPersistentUnitState& Unit) const;

	UFUNCTION(BlueprintCallable, Category = "Morale")
	bool WillRefuseOrder(const FPersistentUnitState& Unit, EOrderType OrderType) const;
};

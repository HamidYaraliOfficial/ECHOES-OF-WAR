#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "EquipmentModel.h"
#include "UnitBase.generated.h"

/**
 * Persistent, saveable state for one unit/squad. This is the "units are not
 * just a number" backbone: experience, fatigue, morale, equipment condition,
 * training, supply status, casualties, command quality and combat history
 * all live here and persist across battles and Save/Load.
 */
USTRUCT(BlueprintType)
struct UNITS_API FPersistentUnitState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FUnitId Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	EUnitCategory Category = EUnitCategory::Infantry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FFactionId OwningFaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FRegionId CurrentRegion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit", meta = (ClampMin = "0", ClampMax = "1"))
	float Experience = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit", meta = (ClampMin = "0", ClampMax = "1"))
	float Fatigue = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FNormalizedRating Morale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit", meta = (ClampMin = "0", ClampMax = "1"))
	float TrainingLevel = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit", meta = (ClampMin = "0", ClampMax = "1"))
	float SupplyStatus = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 AuthorizedStrength = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 CurrentStrength = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 TotalCasualtiesSuffered = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 TotalCasualtiesInflicted = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit", meta = (ClampMin = "0", ClampMax = "1"))
	float CommandQuality = 0.5f; // set by the assigned commander's Leadership stat

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	TArray<FEquipmentInstance> Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	TArray<FString> CombatHistoryLog; // localization keys + params, resolved by UI

	float GetCombatEffectiveness() const
	{
		const float StrengthRatio = AuthorizedStrength > 0 ? (float)CurrentStrength / (float)AuthorizedStrength : 0.f;
		const float MoraleFactor = 0.3f + 0.7f * Morale.Value;
		const float FatigueFactor = 1.f - Fatigue * 0.6f;
		const float SupplyFactor = 0.4f + 0.6f * SupplyStatus;
		const float ExperienceFactor = 0.7f + 0.3f * Experience;
		return FMath::Clamp(StrengthRatio * MoraleFactor * FatigueFactor * SupplyFactor * ExperienceFactor * CommandQuality * 2.f, 0.f, 2.f);
	}
};

UCLASS()
class UNITS_API UUnitStateLibrary : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Unit")
	static void ApplyCasualties(UPARAM(ref) FPersistentUnitState& Unit, int32 Casualties);

	UFUNCTION(BlueprintCallable, Category = "Unit")
	static void GrantExperience(UPARAM(ref) FPersistentUnitState& Unit, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Unit")
	static void ApplyRestAndResupply(UPARAM(ref) FPersistentUnitState& Unit, float RestHours, float SupplyDelivered);
};

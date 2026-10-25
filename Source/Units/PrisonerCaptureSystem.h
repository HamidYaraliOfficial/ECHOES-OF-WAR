#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "PrisonerCaptureSystem.generated.h"

USTRUCT(BlueprintType)
struct UNITS_API FPrisonerRecord
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prisoners")
	FUnitId OriginalUnit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prisoners")
	FFactionId CapturedBy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prisoners")
	FFactionId OriginalOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prisoners")
	int32 Count = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prisoners")
	FRegionId HeldAtRegion;
};

/**
 * Strategic-level POW tracking: encircled/overwhelmed units may surrender
 * rather than be destroyed outright, and captured personnel become a
 * diplomatic/strategic asset (exchange, release, or attrition).
 */
UCLASS()
class UNITS_API UPrisonerCaptureSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Prisoners")
	bool EvaluateSurrenderCondition(float CombatEffectiveness, bool bEncircled, float Morale) const;

	UFUNCTION(BlueprintCallable, Category = "Prisoners")
	void RegisterCapture(const FUnitId& Unit, const FFactionId& CapturedBy, const FFactionId& OriginalOwner, int32 Count, const FRegionId& Region);

	UPROPERTY()
	TArray<FPrisonerRecord> Records;
};

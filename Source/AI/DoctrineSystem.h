#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "DoctrineSystem.generated.h"

/**
 * A faction's military doctrine: weights that bias every AI decision
 * (defence-first vs mobile-warfare vs fire-support-heavy, etc). Doctrines
 * are data-driven and can be upgraded via Research.
 */
USTRUCT(BlueprintType)
struct AI_API FDoctrineProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doctrine")
	FName DoctrineId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doctrine", meta = (ClampMin = "0", ClampMax = "2"))
	float DefensivePreference = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doctrine", meta = (ClampMin = "0", ClampMax = "2"))
	float MobilityPreference = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doctrine", meta = (ClampMin = "0", ClampMax = "2"))
	float FireSupportPreference = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doctrine", meta = (ClampMin = "0", ClampMax = "2"))
	float LogisticsPreference = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doctrine", meta = (ClampMin = "0", ClampMax = "2"))
	float RiskTolerance = 1.f;
};

UCLASS()
class AI_API UDoctrineSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Doctrine")
	void RegisterDoctrine(const FDoctrineProfile& Profile);

	UFUNCTION(BlueprintCallable, Category = "Doctrine")
	bool GetDoctrine(FName DoctrineId, FDoctrineProfile& OutProfile) const;

	UPROPERTY()
	TArray<FDoctrineProfile> Doctrines;
};

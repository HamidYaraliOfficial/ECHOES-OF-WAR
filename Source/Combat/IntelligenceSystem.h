#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "IntelligenceSystem.generated.h"

/** One piece of intel, always carrying a confidence level - never ground truth by default. */
USTRUCT(BlueprintType)
struct COMBAT_API FIntelReport
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intel")
	FRegionId Region;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intel")
	EIntelSourceType SourceType = EIntelSourceType::Scout;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intel")
	float EstimatedEnemyStrength = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intel", meta = (ClampMin = "0", ClampMax = "1"))
	float ConfidenceLevel = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intel")
	float ReportedAtSimHour = 0.f;
};

/**
 * Aggregates Recon, Surveillance, SIGINT, HUMINT, drone feeds and satellite
 * passes into per-region estimates. Reports can disagree; the player and AI
 * must weigh confidence rather than trust a single perfect number.
 */
UCLASS()
class COMBAT_API UIntelligenceSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Intel")
	void SubmitReport(const FIntelReport& Report);

	/** Confidence-weighted average across all reports still fresh enough to matter. */
	UFUNCTION(BlueprintCallable, Category = "Intel")
	float GetBestEstimate(const FRegionId& Region, float CurrentSimHour, float MaxAgeHours, float& OutAggregateConfidence) const;

	UPROPERTY()
	TArray<FIntelReport> Reports;

private:
	static float GetSourceReliability(EIntelSourceType SourceType);
};

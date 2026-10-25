#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "AchievementSystem.generated.h"

/**
 * Multi-metric scoring: an operation/campaign score is never just "enemies
 * defeated" - it blends objective completion, resource efficiency, unit
 * preservation and strategic stability so the game rewards good
 * commandership, not just attrition.
 */
USTRUCT(BlueprintType)
struct UI_API FOperationScoreBreakdown
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score", meta = (ClampMin = "0", ClampMax = "1"))
	float ObjectiveCompletion = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score", meta = (ClampMin = "0", ClampMax = "1"))
	float ResourceEfficiency = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score", meta = (ClampMin = "0", ClampMax = "1"))
	float UnitPreservation = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score", meta = (ClampMin = "0", ClampMax = "1"))
	float StrategicStability = 0.f;

	float GetComposite() const
	{
		return ObjectiveCompletion * 0.4f + ResourceEfficiency * 0.2f
			+ UnitPreservation * 0.25f + StrategicStability * 0.15f;
	}
};

USTRUCT(BlueprintType)
struct UI_API FAchievementDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	FName AchievementId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	FString LocalizationKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement", meta = (ClampMin = "0", ClampMax = "1"))
	float RequiredCompositeScore = 0.7f;
};

UCLASS()
class UI_API UAchievementSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Achievement")
	void RegisterAchievement(const FAchievementDefinition& Definition);

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	TArray<FName> EvaluateUnlocks(const FOperationScoreBreakdown& Score, const TSet<FName>& AlreadyUnlocked) const;

	UPROPERTY()
	TArray<FAchievementDefinition> Definitions;
};

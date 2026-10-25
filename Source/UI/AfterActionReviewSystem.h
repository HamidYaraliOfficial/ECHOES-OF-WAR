#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "AchievementSystem.h"
#include "AfterActionReviewSystem.generated.h"

/** The complete post-operation report shown to the player. */
USTRUCT(BlueprintType)
struct UI_API FAfterActionReport
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	FString OperationName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	TArray<FString> ObjectivesLog; // localization keys, resolved by UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	TArray<FUnitId> UnitsUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	int32 TotalCasualties = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	float SupplyConsumed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	TArray<FRegionId> TerritoryGained;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	TArray<FRegionId> TerritoryLost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	TArray<FWarLogEntry> Timeline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAR")
	FOperationScoreBreakdown Score;
};

/**
 * Assembles a complete After Action Review from the events, casualties and
 * territory changes logged during one operation. Statistics are also rolled
 * up to Unit / Commander / Operation / Campaign / Faction levels elsewhere
 * (Save module) for long-term tracking.
 */
UCLASS()
class UI_API UAfterActionReviewSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "AAR")
	FAfterActionReport BuildReport(const FString& OperationName, const TArray<FWarLogEntry>& OperationEvents,
		const TArray<FUnitId>& UnitsInvolved, int32 Casualties, float SupplyUsed,
		const TArray<FRegionId>& Gained, const TArray<FRegionId>& Lost, const FOperationScoreBreakdown& Score) const;
};

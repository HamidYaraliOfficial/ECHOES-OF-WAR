#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "WarNewsSystem.generated.h"

USTRUCT(BlueprintType)
struct UI_API FWarNewsItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	FDateTime SimulatedTimestamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	FString HeadlineLocalizationKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	TMap<FString, FString> Params;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	FRegionId RelatedRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	bool bIsRadioBroadcast = false;
};

/**
 * Converts FWarLogEntry world events into player-facing news items (map
 * reports, radio broadcasts, command briefings). Every item is generated
 * from an actual logged world event - never scripted filler unrelated to
 * the current campaign state.
 */
UCLASS()
class UI_API UWarNewsSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "News")
	void PublishFromLogEntry(const FWarLogEntry& LogEntry, bool bAsRadioBroadcast);

	UFUNCTION(BlueprintCallable, Category = "News")
	TArray<FWarNewsItem> GetRecentNews(int32 MaxCount) const;

	UPROPERTY()
	TArray<FWarNewsItem> Feed;
};

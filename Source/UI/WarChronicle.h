#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "WarChronicle.generated.h"

/**
 * The full, permanent Campaign timeline: every significant event, in order,
 * queryable by day range, region or faction. Distinct from the WarNewsSystem
 * (recent/ephemeral) - the Chronicle is the historical record the player can
 * browse at any time, including after the campaign ends.
 */
UCLASS()
class UI_API UWarChronicle : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Chronicle")
	void RecordEvent(const FWarLogEntry& Entry);

	UFUNCTION(BlueprintCallable, Category = "Chronicle")
	TArray<FWarLogEntry> QueryByRegion(const FRegionId& Region) const;

	UFUNCTION(BlueprintCallable, Category = "Chronicle")
	TArray<FWarLogEntry> QueryByFaction(const FFactionId& Faction) const;

	UPROPERTY()
	TArray<FWarLogEntry> AllEvents;
};

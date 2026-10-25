#pragma once
#include "CoreMinimal.h"
#include "CampaignSaveData.h"
#include "SaveGameSystem.generated.h"

USTRUCT(BlueprintType)
struct SAVE_API FSaveSlotInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FString SlotName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FDateTime Timestamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	bool bIsAutoSave = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	bool bIsCorrupt = false;
};

/**
 * Handles multiple save slots, auto-save/manual-save/checkpoints, integrity
 * verification and version migration. Designed so a corrupt or
 * older-version save degrades gracefully (flagged, not silently loaded).
 */
UCLASS()
class SAVE_API USaveGameSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Save")
	FString ComputeChecksum(const UCampaignSaveData* SaveData) const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool ValidateIntegrity(const UCampaignSaveData* SaveData) const;

	/** Applies migration steps in sequence so any older save can reach the
	 *  current SaveFormatVersion before being used. */
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool MigrateToCurrentVersion(UPARAM(ref) UCampaignSaveData* SaveData, int32 TargetVersion);

	static constexpr int32 CurrentSaveFormatVersion = 1;
};

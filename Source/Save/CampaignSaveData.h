#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CoreTypes.h"
#include "CampaignSaveData.generated.h"

/**
 * Root save object for one campaign slot. Kept as plain serializable data
 * (no engine object references) so it can be versioned, migrated and
 * validated independently of any particular UE5 version's object layout.
 */
UCLASS()
class SAVE_API UCampaignSaveData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "Save")
	int32 SaveFormatVersion = 1;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	FDateTime SavedAtRealTime;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	FString ScenarioId;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	int32 CurrentSimDay = 0;

	/** Serialized (JSON) blobs per subsystem - keeps this class decoupled
	 *  from every gameplay module's concrete types, avoiding a dependency
	 *  cycle and letting each module version its own save chunk. */
	UPROPERTY(VisibleAnywhere, Category = "Save")
	TMap<FString, FString> SubsystemBlobsJson;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	FString IntegrityChecksum;
};

#pragma once
#include "CoreMinimal.h"
#include "ModLoader.generated.h"

/** Manifest describing one installed mod - loaded from Mods/<ModId>/mod.json. */
USTRUCT(BlueprintType)
struct TOOLS_API FModManifest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString ModId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString Author;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString TargetGameVersion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	TArray<FString> DataFiles; // Scenario/Faction/Unit/Map/Technology/Doctrine/Event JSON paths
};

/**
 * Loads user-created content (scenarios, factions, units, map data,
 * technology, doctrines, events) from Mods/ without touching the core
 * engine build. Validates each manifest's TargetGameVersion before use so
 * incompatible mods fail loudly instead of corrupting a campaign.
 */
UCLASS()
class TOOLS_API UModLoader : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Modding")
	bool ParseManifestJson(const FString& JsonText, FModManifest& OutManifest) const;

	UFUNCTION(BlueprintCallable, Category = "Modding")
	bool IsCompatible(const FModManifest& Manifest, const FString& CurrentGameVersion) const;

	UPROPERTY()
	TArray<FModManifest> LoadedMods;
};

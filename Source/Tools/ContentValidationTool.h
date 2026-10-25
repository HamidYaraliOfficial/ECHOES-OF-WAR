#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "MapDataAsset.h"
#include "ContentValidationTool.generated.h"

USTRUCT(BlueprintType)
struct TOOLS_API FContentValidationIssue
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")
	FString IssueType; // "MissingReference", "DuplicateId", "BrokenScenario", "MissingLocalization", ...
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")
	bool bIsFatal = false;
};

/**
 * Editor-only content validator: catches missing references, invalid data,
 * duplicate ids, broken scenarios, impossible objectives, missing
 * localization strings and circular dependencies before a build ships.
 * Intended to run as a pre-build/CI step (see Scripts/run-tests.ps1).
 */
UCLASS()
class TOOLS_API UContentValidationTool : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Validation")
	TArray<FContentValidationIssue> ValidateMap(const UMapDataAsset* Map) const;

	UFUNCTION(BlueprintCallable, Category = "Validation")
	TArray<FContentValidationIssue> ValidateLocalizationCoverage(const TArray<FString>& RequiredKeys,
		const TMap<FString, FString>& LanguageTable, const FString& LanguageName) const;
};

#pragma once
#include "CoreMinimal.h"
#include "AutomatedScenarioTestRunner.generated.h"

USTRUCT(BlueprintType)
struct TOOLS_API FScenarioTestResult
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	FString ScenarioId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	bool bPassed = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	TArray<FString> FailureReasons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	int32 SimDaysCompleted = 0;
};

/**
 * Runs a scenario headlessly (no GUI, no render) for N simulated days to
 * confirm the AI does not deadlock, the economy does not collapse to zero
 * on turn one, and mission conditions remain reachable. Intended for CI
 * (see Scripts/run-tests.ps1) so regressions are caught before merge.
 */
UCLASS()
class TOOLS_API UAutomatedScenarioTestRunner : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Testing")
	FScenarioTestResult RunHeadless(const FString& ScenarioId, int32 SimDaysToRun);
};

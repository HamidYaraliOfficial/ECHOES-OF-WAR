#pragma once
#include "CoreMinimal.h"
#include "FactionAICommander.h"
#include "AIDebugger.generated.h"

/**
 * Turns FAIDecision::ReasoningTrace into a readable debug feed for
 * developers (and, in Sandbox mode, curious players) so every AI action
 * can be traced back to the world-state numbers that produced it.
 */
UCLASS()
class AI_API UAIDebugger : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "AI Debug")
	FString FormatDecisionReport(const FAIDecision& Decision) const;

	UFUNCTION(BlueprintCallable, Category = "AI Debug")
	FString FormatCycleReport(const TArray<FAIDecision>& Decisions) const;
};

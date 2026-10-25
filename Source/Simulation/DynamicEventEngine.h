#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "WorldSimulationSubsystem.h"
#include "DynamicEventEngine.generated.h"

/** A condition that must hold true against world state for an event to be eligible. */
USTRUCT(BlueprintType)
struct SIMULATION_API FEventCondition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FName ConditionKey; // e.g. "Region.Security.Below", "Faction.Supply.Below"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FName TargetId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	float Threshold = 0.f;
};

/** Data-driven definition of one possible dynamic event (loaded from Content/Data). */
USTRUCT(BlueprintType)
struct SIMULATION_API FDynamicEventDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FName EventId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FString LocalizationKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	TArray<FEventCondition> Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	float BaseWeight = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FName OutcomeHandlerTag; // resolved by gameplay code that applies the effect
};

/**
 * Generates world events strictly from current simulation state (never a
 * pure dice roll with no grounding): a factory can only "break down" if its
 * region has low infrastructure/security, a supply crisis event only fires
 * where a faction's supply is actually strained, etc. Conditions are
 * data-driven so designers can add events without touching C++.
 */
UCLASS()
class SIMULATION_API UDynamicEventEngine : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Events")
	void RegisterDefinition(const FDynamicEventDefinition& Definition);

	UFUNCTION(BlueprintCallable, Category = "Events")
	bool EvaluateCondition(const FEventCondition& Condition, UWorldSimulationSubsystem* WorldSim) const;

	/** Returns event ids whose conditions currently hold, weighted-random one pick per region. */
	UFUNCTION(BlueprintCallable, Category = "Events")
	TArray<FName> RollEligibleEvents(UWorldSimulationSubsystem* WorldSim, int32 MaxEvents) const;

	UPROPERTY()
	TArray<FDynamicEventDefinition> Definitions;
};

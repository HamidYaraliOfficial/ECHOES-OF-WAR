#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "DoctrineSystem.h"
#include "WorldSimulationSubsystem.h"
#include "FactionAICommander.generated.h"

/** One concrete decision the strategic AI has made this evaluation cycle. */
USTRUCT(BlueprintType)
struct AI_API FAIDecision
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName DecisionType; // "Reinforce", "Attack", "Retreat", "RequestCeasefire", "ShiftProduction"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FRegionId TargetRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Priority = 0.f;
	/** Human-readable, localizable reasoning trail - consumed by the AI Debugger. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<FString> ReasoningTrace;
};

/**
 * Strategic-level AI "brain" for one non-player faction. Reads only from the
 * shared WorldSimulationSubsystem (the same data the player can see through
 * Fog of War / Intelligence, never a hidden omniscient channel), and
 * produces a ranked list of decisions each evaluation cycle. Never invents
 * numbers, so every decision can be explained by the AI Debugger.
 */
UCLASS()
class AI_API UFactionAICommander : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FFactionId ControlledFaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FDoctrineProfile Doctrine;

	/** Known intel about other factions' strength per region - populated by
	 *  the Intelligence system, may be incomplete/wrong (confidence < 1). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TMap<FRegionId, float> KnownEnemyStrengthEstimate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TMap<FRegionId, float> OwnDeployedStrength;

	UFUNCTION(BlueprintCallable, Category = "AI")
	TArray<FAIDecision> EvaluateStrategicCycle(UWorldSimulationSubsystem* WorldSim);

private:
	FAIDecision EvaluateRegionForReinforcement(const FRegionState& Region) const;
	FAIDecision EvaluateRegionForAttack(const FRegionState& Region) const;
	bool ShouldConsiderCeasefire(const TArray<FRegionId>& OwnedRegions) const;
};

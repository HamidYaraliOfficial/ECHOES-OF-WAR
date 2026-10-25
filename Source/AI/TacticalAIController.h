#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "CoreTypes.h"
#include "TacticalAIController.generated.h"

/** Snapshot of what one AI-controlled unit currently perceives - never omniscient. */
USTRUCT(BlueprintType)
struct AI_API FTacticalPerception
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float VisibleEnemyStrength = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float OwnStrength = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float OwnMorale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float OwnSupplyLevel = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	ETerrainType LocalTerrain = ETerrainType::Plains;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	bool bUnderSuppression = false;
};

UENUM(BlueprintType)
enum class ETacticalDecision : uint8
{
	HoldPosition, AdvanceAndEngage, SuppressAndFlank, FallBack, CallForSupport, Surrender
};

/**
 * Squad/unit-level combat AI. Consumes only FTacticalPerception (what this
 * unit can actually see/know) and the unit's own doctrine bias, and returns
 * one tactical decision per evaluation tick. This is the lowest layer of the
 * three-layer (Squad -> Commander -> Army) AI decision hierarchy.
 */
UCLASS()
class AI_API ATacticalAIController : public AAIController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Tactical AI")
	ETacticalDecision EvaluateTacticalDecision(const FTacticalPerception& Perception, float RiskTolerance) const;
};

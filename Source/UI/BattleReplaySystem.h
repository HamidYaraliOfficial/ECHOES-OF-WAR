#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "BattleReplaySystem.generated.h"

/** One recorded frame of a unit's position/state during a battle, for replay scrubbing. */
USTRUCT(BlueprintType)
struct UI_API FReplayFrame
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replay")
	float SimTimeSeconds = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replay")
	FUnitId Unit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replay")
	FVector2D Position = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replay")
	float CombatEffectivenessAtFrame = 1.f;
};

/**
 * Records every command and significant event during a battle so it can be
 * scrubbed back later with free/tactical/overhead cameras, plus derived
 * heatmaps (movement density, frontline evolution, supply flow).
 */
UCLASS()
class UI_API UBattleReplaySystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Replay")
	void RecordFrame(const FReplayFrame& Frame);

	UFUNCTION(BlueprintCallable, Category = "Replay")
	TArray<FReplayFrame> GetFramesInRange(float StartTime, float EndTime) const;

	/** Builds a coarse 2D movement-density grid usable for a heatmap overlay. */
	UFUNCTION(BlueprintCallable, Category = "Replay")
	TMap<FIntPoint, int32> BuildMovementHeatmap(int32 GridCellSize) const;

	UPROPERTY()
	TArray<FReplayFrame> Frames;
};

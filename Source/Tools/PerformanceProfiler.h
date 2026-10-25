#pragma once
#include "CoreMinimal.h"
#include "PerformanceProfiler.generated.h"

USTRUCT(BlueprintType)
struct TOOLS_API FPerformanceSnapshot
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float FPS = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float FrameTimeMs = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float SimulationCostMs = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float AICostMs = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float MemoryUsedMB = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 DrawCalls = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 StreamedLevelsActive = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float NetworkCostMs = 0.f;
};

/**
 * Lightweight in-house profiler overlay: aggregates per-frame cost across
 * the render thread, the decoupled simulation thread and background
 * workers, so heavy world simulation is visibly never allowed to stall UI.
 */
UCLASS()
class TOOLS_API UPerformanceProfiler : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Performance")
	void RecordSnapshot(const FPerformanceSnapshot& Snapshot);

	UFUNCTION(BlueprintCallable, Category = "Performance")
	FPerformanceSnapshot GetAverageOverLastNFrames(int32 N) const;

	UPROPERTY()
	TArray<FPerformanceSnapshot> History;
};

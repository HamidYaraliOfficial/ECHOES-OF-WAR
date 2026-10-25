#include "PerformanceProfiler.h"

void UPerformanceProfiler::RecordSnapshot(const FPerformanceSnapshot& Snapshot)
{
	History.Add(Snapshot);
	if (History.Num() > 600) History.RemoveAt(0); // keep ~10s at 60fps
}

FPerformanceSnapshot UPerformanceProfiler::GetAverageOverLastNFrames(int32 N) const
{
	FPerformanceSnapshot Avg;
	const int32 Count = FMath::Min(N, History.Num());
	if (Count == 0) return Avg;

	for (int32 i = History.Num() - Count; i < History.Num(); ++i)
	{
		Avg.FPS += History[i].FPS;
		Avg.FrameTimeMs += History[i].FrameTimeMs;
		Avg.SimulationCostMs += History[i].SimulationCostMs;
		Avg.AICostMs += History[i].AICostMs;
		Avg.MemoryUsedMB += History[i].MemoryUsedMB;
		Avg.DrawCalls += History[i].DrawCalls;
		Avg.NetworkCostMs += History[i].NetworkCostMs;
	}
	Avg.FPS /= Count; Avg.FrameTimeMs /= Count; Avg.SimulationCostMs /= Count;
	Avg.AICostMs /= Count; Avg.MemoryUsedMB /= Count; Avg.DrawCalls /= Count; Avg.NetworkCostMs /= Count;
	return Avg;
}

#include "BattleReplaySystem.h"

void UBattleReplaySystem::RecordFrame(const FReplayFrame& Frame)
{
	Frames.Add(Frame);
}

TArray<FReplayFrame> UBattleReplaySystem::GetFramesInRange(float StartTime, float EndTime) const
{
	TArray<FReplayFrame> Result;
	for (const FReplayFrame& Frame : Frames)
	{
		if (Frame.SimTimeSeconds >= StartTime && Frame.SimTimeSeconds <= EndTime) Result.Add(Frame);
	}
	return Result;
}

TMap<FIntPoint, int32> UBattleReplaySystem::BuildMovementHeatmap(int32 GridCellSize) const
{
	TMap<FIntPoint, int32> Heatmap;
	for (const FReplayFrame& Frame : Frames)
	{
		const FIntPoint Cell(FMath::FloorToInt(Frame.Position.X / GridCellSize),
			FMath::FloorToInt(Frame.Position.Y / GridCellSize));
		Heatmap.FindOrAdd(Cell)++;
	}
	return Heatmap;
}

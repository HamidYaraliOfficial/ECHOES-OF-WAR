#include "WarNewsSystem.h"

void UWarNewsSystem::PublishFromLogEntry(const FWarLogEntry& LogEntry, bool bAsRadioBroadcast)
{
	FWarNewsItem Item;
	Item.SimulatedTimestamp = LogEntry.SimulatedTimestamp;
	Item.HeadlineLocalizationKey = LogEntry.LocalizationKey;
	Item.Params = LogEntry.Parameters;
	Item.RelatedRegion = LogEntry.RelatedRegion;
	Item.bIsRadioBroadcast = bAsRadioBroadcast;
	Feed.Insert(Item, 0);
}

TArray<FWarNewsItem> UWarNewsSystem::GetRecentNews(int32 MaxCount) const
{
	TArray<FWarNewsItem> Result = Feed;
	if (Result.Num() > MaxCount) Result.SetNum(MaxCount);
	return Result;
}

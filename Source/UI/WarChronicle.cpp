#include "WarChronicle.h"

void UWarChronicle::RecordEvent(const FWarLogEntry& Entry)
{
	AllEvents.Add(Entry);
}

TArray<FWarLogEntry> UWarChronicle::QueryByRegion(const FRegionId& Region) const
{
	TArray<FWarLogEntry> Result;
	for (const FWarLogEntry& Entry : AllEvents)
	{
		if (Entry.RelatedRegion == Region) Result.Add(Entry);
	}
	return Result;
}

TArray<FWarLogEntry> UWarChronicle::QueryByFaction(const FFactionId& Faction) const
{
	TArray<FWarLogEntry> Result;
	for (const FWarLogEntry& Entry : AllEvents)
	{
		if (Entry.RelatedFaction == Faction) Result.Add(Entry);
	}
	return Result;
}

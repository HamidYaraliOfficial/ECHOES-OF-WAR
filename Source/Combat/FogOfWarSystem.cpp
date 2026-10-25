#include "FogOfWarSystem.h"

void UFogOfWarSystem::MarkObserved(const FFactionId& Observer, const FRegionId& Region, EIntelSourceType SourceType, float SimHour)
{
	TMap<FRegionId, FRegionVisibility>& FactionMap = VisibilityByFaction.FindOrAdd(Observer);
	FRegionVisibility& Vis = FactionMap.FindOrAdd(Region);
	Vis.State = EVisibilityState::Visible;
	Vis.LastSeenSimHour = SimHour;
	Vis.LastSourceType = SourceType;
}

void UFogOfWarSystem::DecayStaleVisibility(float CurrentSimHour, float StaleAfterHours)
{
	for (auto& FactionPair : VisibilityByFaction)
	{
		for (auto& RegionPair : FactionPair.Value)
		{
			if (RegionPair.Value.State == EVisibilityState::Visible &&
				CurrentSimHour - RegionPair.Value.LastSeenSimHour > StaleAfterHours)
			{
				RegionPair.Value.State = EVisibilityState::PreviouslySeen;
			}
		}
	}
}

EVisibilityState UFogOfWarSystem::GetVisibility(const FFactionId& Observer, const FRegionId& Region) const
{
	if (const TMap<FRegionId, FRegionVisibility>* FactionMap = VisibilityByFaction.Find(Observer))
	{
		if (const FRegionVisibility* Vis = FactionMap->Find(Region))
		{
			return Vis->State;
		}
	}
	return EVisibilityState::Unexplored;
}

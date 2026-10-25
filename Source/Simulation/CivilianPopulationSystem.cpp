#include "CivilianPopulationSystem.h"

float UCivilianPopulationSystem::GetHumanitarianNeedIndex(const FRegionState& Region) const
{
	const float DisplacementFactor = Region.Population > 0
		? (float)Region.DisplacedPopulation / (float)FMath::Max(1, Region.Population + Region.DisplacedPopulation)
		: 0.f;
	const float MoraleFactor = 1.f - Region.CivilianMorale.Value;
	const float EmploymentFactor = 1.f - Region.Employment.Value;
	return FMath::Clamp(DisplacementFactor * 0.5f + MoraleFactor * 0.3f + EmploymentFactor * 0.2f, 0.f, 1.f);
}

void UCivilianPopulationSystem::ApplyAidShipment(FRegionState& Region, float AidAmount)
{
	Region.CivilianMorale.Add(AidAmount * 0.05f);
	Region.Employment.Add(AidAmount * 0.02f);
	const int32 Resettled = FMath::Min(Region.DisplacedPopulation, FMath::RoundToInt(AidAmount * 10.f));
	Region.DisplacedPopulation -= Resettled;
	Region.Population += Resettled;
}

int32 UCivilianPopulationSystem::GetTotalDisplaced(UWorldSimulationSubsystem* WorldSim) const
{
	int32 Total = 0;
	if (!WorldSim) return Total;
	for (const FRegionId& Id : WorldSim->GetAllRegionIds())
	{
		FRegionState Region;
		if (WorldSim->GetRegion(Id, Region)) Total += Region.DisplacedPopulation;
	}
	return Total;
}

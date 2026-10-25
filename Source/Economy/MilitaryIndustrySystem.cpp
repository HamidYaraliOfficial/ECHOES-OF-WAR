#include "MilitaryIndustrySystem.h"

float UMilitaryIndustrySystem::ComputeActualOutput(const FFactoryState& Factory, FFactionEconomy& Economy)
{
	const float CapacityFactor = Factory.PowerAvailability * Factory.LaborAvailability * Factory.SecurityLevel;
	float DesiredOutput = Factory.BaseOutputPerDay * CapacityFactor;

	// Clamp desired output by whatever input resource is scarcest.
	for (const auto& Pair : Factory.InputRequirementPerUnit)
	{
		const float Available = Economy.Stockpiles.Contains(Pair.Key) ? Economy.Stockpiles[Pair.Key] : 0.f;
		const float MaxUnitsFromThisResource = Pair.Value > 0.f ? Available / Pair.Value : DesiredOutput;
		DesiredOutput = FMath::Min(DesiredOutput, MaxUnitsFromThisResource);
	}

	// Consume the inputs actually used.
	for (const auto& Pair : Factory.InputRequirementPerUnit)
	{
		float& Stock = Economy.Stockpiles.FindOrAdd(Pair.Key, 0.f);
		Stock = FMath::Max(0.f, Stock - Pair.Value * DesiredOutput);
	}

	return FMath::Max(0.f, DesiredOutput);
}

void UMilitaryIndustrySystem::RelocateFactory(FFactoryState& Factory, const FRegionId& NewRegion, float DisruptionDays)
{
	Factory.HostRegion = NewRegion;
	// Relocation temporarily halves output; caller is expected to ramp
	// PowerAvailability/LaborAvailability back up over DisruptionDays.
	Factory.PowerAvailability *= 0.5f;
	Factory.LaborAvailability *= 0.5f;
}

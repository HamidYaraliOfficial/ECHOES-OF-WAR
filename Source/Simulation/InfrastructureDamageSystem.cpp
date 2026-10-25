#include "InfrastructureDamageSystem.h"

void UInfrastructureDamageSystem::QueueRepair(const FRegionId& Region, EInfrastructureType Target, float EngineeringPoints)
{
	FRepairJob Job;
	Job.Region = Region;
	Job.Target = Target;
	Job.EngineeringPointsAssigned = EngineeringPoints;
	Job.ProgressRemaining = 1.f;
	ActiveJobs.Add(Job);
}

void UInfrastructureDamageSystem::TickRepairs(UWorldSimulationSubsystem* WorldSim, float DeltaDays)
{
	if (!WorldSim) return;

	for (int32 i = ActiveJobs.Num() - 1; i >= 0; --i)
	{
		FRepairJob& Job = ActiveJobs[i];
		const float RepairRate = Job.EngineeringPointsAssigned * 0.05f * DeltaDays;
		Job.ProgressRemaining -= RepairRate;

		FRegionState Region;
		if (WorldSim->GetRegion(Job.Region, Region))
		{
			float& Integrity = Region.InfrastructureIntegrity.FindOrAdd(Job.Target, 1.f);
			Integrity = FMath::Clamp(Integrity + RepairRate, 0.f, 1.f);
			WorldSim->RegisterRegion(Region); // re-register mutated copy
		}

		if (Job.ProgressRemaining <= 0.f)
		{
			ActiveJobs.RemoveAt(i);
		}
	}
}

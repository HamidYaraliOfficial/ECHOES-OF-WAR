#include "FrontlineSimulation.h"

void UFrontlineSimulation::UpdateSegment(FFrontlineSegment& Segment, float TerrainDefenseBonus, float WeatherModifier, float DeltaDays)
{
	const float EffectiveDefense = Segment.DefenderCombatPower * (1.f + TerrainDefenseBonus);
	const float EffectiveAttack = Segment.AttackerCombatPower * WeatherModifier;

	const float NetPressure = (EffectiveAttack - EffectiveDefense) / FMath::Max(1.f, EffectiveAttack + EffectiveDefense);
	Segment.PressureBalance = FMath::Clamp(Segment.PressureBalance - NetPressure * 0.1f * DeltaDays, -1.f, 1.f);
}

bool UFrontlineSimulation::TryResolveCapture(const FFrontlineSegment& Segment, UWorldSimulationSubsystem* WorldSim)
{
	if (!WorldSim) return false;
	if (Segment.PressureBalance <= -0.95f)
	{
		WorldSim->SetRegionController(Segment.Region, Segment.AttackingFaction);
		return true;
	}
	return false;
}

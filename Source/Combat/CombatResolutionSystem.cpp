#include "CombatResolutionSystem.h"

float UCombatResolutionSystem::ComputeUnitContribution(const FPersistentUnitState& Unit) const
{
	return Unit.GetCombatEffectiveness() * FMath::Max(1, Unit.CurrentStrength);
}

FCombatResult UCombatResolutionSystem::ResolveEngagement(float AttackerPower, float DefenderPower, float TerrainDefenseBonus, float WeatherModifier) const
{
	FCombatResult Result;
	const float EffectiveDefender = DefenderPower * (1.f + TerrainDefenseBonus);
	const float EffectiveAttacker = AttackerPower * WeatherModifier;
	const float Total = FMath::Max(1.f, EffectiveAttacker + EffectiveDefender);

	Result.bAttackerWon = EffectiveAttacker > EffectiveDefender;
	Result.DefenderCasualtyRatio = FMath::Clamp(EffectiveAttacker / Total * 0.4f, 0.f, 0.9f);
	Result.AttackerCasualtyRatio = FMath::Clamp(EffectiveDefender / Total * 0.4f, 0.f, 0.9f);
	return Result;
}

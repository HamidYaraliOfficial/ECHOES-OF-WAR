#include "TacticalAIController.h"

ETacticalDecision ATacticalAIController::EvaluateTacticalDecision(const FTacticalPerception& Perception, float RiskTolerance) const
{
	// Morale/supply collapse overrides everything else.
	if (Perception.OwnMorale < 0.15f && Perception.OwnSupplyLevel < 0.2f)
	{
		return Perception.OwnMorale < 0.05f ? ETacticalDecision::Surrender : ETacticalDecision::FallBack;
	}

	if (Perception.bUnderSuppression && Perception.OwnMorale < 0.4f)
	{
		return ETacticalDecision::FallBack;
	}

	const float TerrainDefenseBonus =
		(Perception.LocalTerrain == ETerrainType::Urban || Perception.LocalTerrain == ETerrainType::Mountains) ? 0.3f : 0.f;

	const float CombatRatio = (Perception.OwnStrength * (1.f + TerrainDefenseBonus))
		/ FMath::Max(0.01f, Perception.VisibleEnemyStrength);

	if (CombatRatio < 0.5f && Perception.OwnSupplyLevel < 0.5f)
	{
		return ETacticalDecision::CallForSupport;
	}

	if (CombatRatio >= 1.3f * (2.f - RiskTolerance))
	{
		return ETacticalDecision::AdvanceAndEngage;
	}

	if (CombatRatio >= 0.8f)
	{
		return Perception.bUnderSuppression ? ETacticalDecision::SuppressAndFlank : ETacticalDecision::HoldPosition;
	}

	return ETacticalDecision::HoldPosition;
}

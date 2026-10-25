#include "FatigueSystem.h"

void UFatigueSystem::AccumulateFromActivity(FPersistentUnitState& Unit, float HoursActive, bool bInCombat, float WeatherSeverity)
{
	float Rate = HoursActive * 0.01f;
	if (bInCombat) Rate *= 2.5f;
	Rate *= (1.f + WeatherSeverity * 0.5f);
	Unit.Fatigue = FMath::Clamp(Unit.Fatigue + Rate, 0.f, 1.f);
}

void UFatigueSystem::ApplyRest(FPersistentUnitState& Unit, float RestHours)
{
	Unit.Fatigue = FMath::Clamp(Unit.Fatigue - RestHours * 0.03f, 0.f, 1.f);
}

bool UFatigueSystem::NeedsRotation(const FPersistentUnitState& Unit) const
{
	return Unit.Fatigue > 0.75f;
}

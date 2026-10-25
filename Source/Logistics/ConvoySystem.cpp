#include "ConvoySystem.h"

void UConvoySystem::AdvanceConvoy(FConvoyState& Convoy, float DeltaDays, float RouteSpeedFactor)
{
	Convoy.ProgressFraction = FMath::Clamp(Convoy.ProgressFraction + DeltaDays * RouteSpeedFactor, 0.f, 1.f);
}

float UConvoySystem::ComputeInterdictionChance(float RouteThreatLevel, bool bEscorted) const
{
	const float Base = RouteThreatLevel * 0.4f;
	return FMath::Clamp(bEscorted ? Base * 0.35f : Base, 0.f, 0.9f);
}

float UConvoySystem::ResolveInterdiction(FConvoyState& Convoy, float RouteThreatLevel)
{
	const float Chance = ComputeInterdictionChance(RouteThreatLevel, Convoy.bEscorted);
	if (FMath::FRand() < Chance)
	{
		const float Lost = Convoy.CargoAmount * FMath::FRandRange(0.2f, 0.6f);
		Convoy.CargoAmount -= Lost;
		return Lost;
	}
	return 0.f;
}

#include "OrderSystem.h"

float UOrderExecutionModel::ComputeExecutionProbability(float CommQuality, float UnitMorale, float Fatigue,
	float OfficerQuality, bool bUnderSuppression, bool bCommsDamaged) const
{
	float Probability = 0.5f + CommQuality * 0.2f + UnitMorale * 0.15f + OfficerQuality * 0.15f - Fatigue * 0.2f;
	if (bUnderSuppression) Probability -= 0.25f;
	if (bCommsDamaged) Probability -= 0.3f;
	return FMath::Clamp(Probability, 0.05f, 0.99f);
}

float UOrderExecutionModel::ComputeCommunicationDelayHours(float CommQuality, float Distance) const
{
	const float BaseDelay = Distance / FMath::Max(1.f, CommQuality * 100.f);
	return FMath::Clamp(BaseDelay, 0.05f, 12.f);
}

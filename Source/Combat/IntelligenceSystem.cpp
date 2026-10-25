#include "IntelligenceSystem.h"

float UIntelligenceSystem::GetSourceReliability(EIntelSourceType SourceType)
{
	switch (SourceType)
	{
		case EIntelSourceType::EngagedUnit: return 0.95f;
		case EIntelSourceType::Satellite: return 0.85f;
		case EIntelSourceType::Drone: return 0.8f;
		case EIntelSourceType::Radar: return 0.75f;
		case EIntelSourceType::ObservationPost: return 0.7f;
		case EIntelSourceType::Signals: return 0.6f;
		case EIntelSourceType::HumanIntel: return 0.5f;
		case EIntelSourceType::Scout: default: return 0.65f;
	}
}

void UIntelligenceSystem::SubmitReport(const FIntelReport& Report)
{
	FIntelReport Adjusted = Report;
	Adjusted.ConfidenceLevel = FMath::Clamp(Adjusted.ConfidenceLevel * GetSourceReliability(Report.SourceType), 0.f, 1.f);
	Reports.Add(Adjusted);
}

float UIntelligenceSystem::GetBestEstimate(const FRegionId& Region, float CurrentSimHour, float MaxAgeHours, float& OutAggregateConfidence) const
{
	float WeightedSum = 0.f;
	float WeightTotal = 0.f;

	for (const FIntelReport& Report : Reports)
	{
		if (!(Report.Region == Region)) continue;
		const float Age = CurrentSimHour - Report.ReportedAtSimHour;
		if (Age > MaxAgeHours) continue;

		const float RecencyFactor = FMath::Clamp(1.f - Age / MaxAgeHours, 0.f, 1.f);
		const float Weight = Report.ConfidenceLevel * RecencyFactor;
		WeightedSum += Report.EstimatedEnemyStrength * Weight;
		WeightTotal += Weight;
	}

	OutAggregateConfidence = FMath::Clamp(WeightTotal, 0.f, 1.f);
	return WeightTotal > 0.f ? WeightedSum / WeightTotal : 0.f;
}

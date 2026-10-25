#include "AfterActionReviewSystem.h"

FAfterActionReport UAfterActionReviewSystem::BuildReport(const FString& OperationName, const TArray<FWarLogEntry>& OperationEvents,
	const TArray<FUnitId>& UnitsInvolved, int32 Casualties, float SupplyUsed,
	const TArray<FRegionId>& Gained, const TArray<FRegionId>& Lost, const FOperationScoreBreakdown& Score) const
{
	FAfterActionReport Report;
	Report.OperationName = OperationName;
	Report.Timeline = OperationEvents;
	Report.UnitsUsed = UnitsInvolved;
	Report.TotalCasualties = Casualties;
	Report.SupplyConsumed = SupplyUsed;
	Report.TerritoryGained = Gained;
	Report.TerritoryLost = Lost;
	Report.Score = Score;

	for (const FWarLogEntry& Entry : OperationEvents)
	{
		Report.ObjectivesLog.Add(Entry.LocalizationKey);
	}
	return Report;
}

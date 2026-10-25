#include "CommandHierarchy.h"

void UCommandHierarchySystem::PromoteCommander(FCommanderProfile& Commander)
{
	if (Commander.Experience < 0.3f) return;
	switch (Commander.Rank)
	{
		case ECommandRank::NCO: Commander.Rank = ECommandRank::JuniorOfficer; break;
		case ECommandRank::JuniorOfficer: Commander.Rank = ECommandRank::FieldOfficer; break;
		case ECommandRank::FieldOfficer: Commander.Rank = ECommandRank::GeneralOfficer; break;
		default: break;
	}
	Commander.Leadership = FMath::Min(1.f, Commander.Leadership + 0.05f);
}

void UCommandHierarchySystem::HandleCommanderCasualty(FCommanderProfile& Commander, bool bCaptured)
{
	if (bCaptured) Commander.bIsCaptured = true;
	else Commander.bIsKIA = true;
}

float UCommandHierarchySystem::GetCommandQualityMultiplier(const FCommanderProfile& Commander) const
{
	if (Commander.bIsKIA || Commander.bIsCaptured) return 0.4f; // leaderless units underperform sharply
	return FMath::Clamp(0.5f + Commander.Leadership * 0.3f + Commander.Experience * 0.2f, 0.3f, 1.3f);
}

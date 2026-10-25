#include "PrisonerCaptureSystem.h"

bool UPrisonerCaptureSystem::EvaluateSurrenderCondition(float CombatEffectiveness, bool bEncircled, float Morale) const
{
	return bEncircled && CombatEffectiveness < 0.15f && Morale < 0.25f;
}

void UPrisonerCaptureSystem::RegisterCapture(const FUnitId& Unit, const FFactionId& CapturedBy, const FFactionId& OriginalOwner, int32 Count, const FRegionId& Region)
{
	FPrisonerRecord Record;
	Record.OriginalUnit = Unit;
	Record.CapturedBy = CapturedBy;
	Record.OriginalOwner = OriginalOwner;
	Record.Count = Count;
	Record.HeldAtRegion = Region;
	Records.Add(Record);
}

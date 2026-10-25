#include "AdvisorSystem.h"

void UAdvisorSystem::SubmitBriefing(const FAdvisorBriefing& Briefing)
{
	ActiveBriefings.Add(Briefing);
}

TArray<FAdvisorBriefing> UAdvisorSystem::GetBriefingsForRole(EAdvisorRole Role) const
{
	TArray<FAdvisorBriefing> Result;
	for (const FAdvisorBriefing& Briefing : ActiveBriefings)
	{
		if (Briefing.Role == Role) Result.Add(Briefing);
	}
	return Result;
}

TArray<FAdvisorBriefing> UAdvisorSystem::GetMostUrgent(int32 MaxCount) const
{
	TArray<FAdvisorBriefing> Sorted = ActiveBriefings;
	Sorted.Sort([](const FAdvisorBriefing& A, const FAdvisorBriefing& B) { return A.Urgency > B.Urgency; });
	if (Sorted.Num() > MaxCount) Sorted.SetNum(MaxCount);
	return Sorted;
}

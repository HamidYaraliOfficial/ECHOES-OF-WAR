#include "AchievementSystem.h"

void UAchievementSystem::RegisterAchievement(const FAchievementDefinition& Definition)
{
	Definitions.Add(Definition);
}

TArray<FName> UAchievementSystem::EvaluateUnlocks(const FOperationScoreBreakdown& Score, const TSet<FName>& AlreadyUnlocked) const
{
	TArray<FName> Newly;
	const float Composite = Score.GetComposite();
	for (const FAchievementDefinition& Def : Definitions)
	{
		if (!AlreadyUnlocked.Contains(Def.AchievementId) && Composite >= Def.RequiredCompositeScore)
		{
			Newly.Add(Def.AchievementId);
		}
	}
	return Newly;
}

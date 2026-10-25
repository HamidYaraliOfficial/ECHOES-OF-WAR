#include "ResearchTree.h"

void UResearchTreeSystem::RegisterNode(const FResearchNode& Node)
{
	Nodes.Add(Node);
}

const FResearchNode* UResearchTreeSystem::FindNode(FName Id) const
{
	for (const FResearchNode& Node : Nodes)
	{
		if (Node.ResearchId == Id) return &Node;
	}
	return nullptr;
}

bool UResearchTreeSystem::CanStartResearch(const FFactionResearchState& State, FName ResearchId) const
{
	const FResearchNode* Node = FindNode(ResearchId);
	if (!Node) return false;
	if (State.CompletedResearch.Contains(ResearchId)) return false;

	for (const FName& Prereq : Node->Prerequisites)
	{
		if (!State.CompletedResearch.Contains(Prereq)) return false;
	}
	return true;
}

bool UResearchTreeSystem::TickResearch(FFactionResearchState& State, float DeltaDays, TArray<FString>& OutNewlyAppliedEffects)
{
	if (State.ActiveResearchId.IsNone()) return false;
	const FResearchNode* Node = FindNode(State.ActiveResearchId);
	if (!Node) return false;

	State.ProgressDaysAccumulated += DeltaDays;
	if (State.ProgressDaysAccumulated >= Node->DurationDays)
	{
		State.CompletedResearch.Add(State.ActiveResearchId);
		OutNewlyAppliedEffects.Add(Node->AppliedEffectTag);
		State.ActiveResearchId = NAME_None;
		State.ProgressDaysAccumulated = 0.f;
		return true;
	}
	return false;
}

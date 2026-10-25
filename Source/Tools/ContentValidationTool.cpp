#include "ContentValidationTool.h"

TArray<FContentValidationIssue> UContentValidationTool::ValidateMap(const UMapDataAsset* Map) const
{
	TArray<FContentValidationIssue> Issues;
	if (!Map)
	{
		Issues.Add({ TEXT("MissingReference"), TEXT("Map asset is null"), true });
		return Issues;
	}

	TSet<FName> SeenIds;
	for (const FSettlementData& Settlement : Map->Settlements)
	{
		if (SeenIds.Contains(Settlement.Id.Value))
		{
			Issues.Add({ TEXT("DuplicateId"), FString::Printf(TEXT("Duplicate region id: %s"), *Settlement.Id.Value.ToString()), true });
		}
		SeenIds.Add(Settlement.Id.Value);
	}

	for (const FInfrastructureLink& Link : Map->InfrastructureLinks)
	{
		if (!SeenIds.Contains(Link.From.Value) || !SeenIds.Contains(Link.To.Value))
		{
			Issues.Add({ TEXT("MissingReference"), FString::Printf(TEXT("Infrastructure link references unknown region (%s -> %s)"),
				*Link.From.Value.ToString(), *Link.To.Value.ToString()), true });
		}
	}

	for (const FResourceNodeData& Node : Map->ResourceNodes)
	{
		if (!SeenIds.Contains(Node.HostRegion.Value))
		{
			Issues.Add({ TEXT("MissingReference"), FString::Printf(TEXT("Resource node references unknown region: %s"), *Node.HostRegion.Value.ToString()), true });
		}
	}

	if (Map->Settlements.Num() == 0)
	{
		Issues.Add({ TEXT("BrokenScenario"), TEXT("Map has no settlements - no valid starting territory"), true });
	}

	return Issues;
}

TArray<FContentValidationIssue> UContentValidationTool::ValidateLocalizationCoverage(const TArray<FString>& RequiredKeys,
	const TMap<FString, FString>& LanguageTable, const FString& LanguageName) const
{
	TArray<FContentValidationIssue> Issues;
	for (const FString& Key : RequiredKeys)
	{
		if (!LanguageTable.Contains(Key))
		{
			Issues.Add({ TEXT("MissingLocalization"), FString::Printf(TEXT("[%s] missing key: %s"), *LanguageName, *Key), false });
		}
	}
	return Issues;
}

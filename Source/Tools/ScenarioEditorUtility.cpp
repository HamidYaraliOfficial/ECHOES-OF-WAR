#include "ScenarioEditorUtility.h"

void UScenarioEditorUtility::CreateNewSettlement(UMapDataAsset* Map, FName RegionId, ESettlementType Type, FVector2D Position)
{
	if (!Map) return;
	FSettlementData Data;
	Data.Id.Value = RegionId;
	Data.Type = Type;
	Data.MapPosition = Position;
	Map->Settlements.Add(Data);
}

void UScenarioEditorUtility::CreateInfrastructureLink(UMapDataAsset* Map, FName From, FName To, EInfrastructureType LinkType)
{
	if (!Map) return;
	FInfrastructureLink Link;
	Link.From.Value = From;
	Link.To.Value = To;
	Link.LinkType = LinkType;
	Map->InfrastructureLinks.Add(Link);
}

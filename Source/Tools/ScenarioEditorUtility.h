#pragma once
#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MapDataAsset.h"
#include "ScenarioEditorUtility.generated.h"

/**
 * Editor Utility Widget base for the Scenario Editor: lets a designer
 * define maps, factions, units, resources, frontlines, missions, events,
 * triggers, technology and AI doctrine entirely through data (this class
 * plus the JSON/DataAsset formats in Content/Data) without editing C++.
 */
UCLASS()
class TOOLS_API UScenarioEditorUtility : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Scenario Editor")
	void CreateNewSettlement(UPARAM(ref) UMapDataAsset* Map, FName RegionId, ESettlementType Type, FVector2D Position);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Scenario Editor")
	void CreateInfrastructureLink(UPARAM(ref) UMapDataAsset* Map, FName From, FName To, EInfrastructureType LinkType);
};

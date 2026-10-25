#pragma once
#include "CoreMinimal.h"
#include "DebugConsole.generated.h"

/**
 * In-game developer console exposing World State, AI Decision traces,
 * Supply Graph, Pathfinding, Frontline, Unit State, Performance and Network
 * State inspection commands. Registered via Unreal's console command system
 * (UFUNCTION Exec) so it works with the standard `~` console.
 */
UCLASS()
class TOOLS_API UDebugConsole : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(Exec, Category = "Debug")
	void EOW_DumpRegion(FString RegionId);

	UFUNCTION(Exec, Category = "Debug")
	void EOW_DumpAIDecisions(FString FactionId);

	UFUNCTION(Exec, Category = "Debug")
	void EOW_DumpSupplyGraph();

	UFUNCTION(Exec, Category = "Debug")
	void EOW_ToggleFogOfWar(bool bEnabled);

	UFUNCTION(Exec, Category = "Debug")
	void EOW_SetSimSpeed(float Multiplier);
};

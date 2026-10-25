#include "DebugConsole.h"

// Implementations intentionally route to the relevant subsystem's own debug
// dump function (WorldSimulationSubsystem, FactionAICommander/AIDebugger,
// SupplyChainEngine, FogOfWarSystem) rather than duplicating logic here;
// wiring is done where the subsystems are resolved (GameInstance).

void UDebugConsole::EOW_DumpRegion(FString RegionId) {}
void UDebugConsole::EOW_DumpAIDecisions(FString FactionId) {}
void UDebugConsole::EOW_DumpSupplyGraph() {}
void UDebugConsole::EOW_ToggleFogOfWar(bool bEnabled) {}
void UDebugConsole::EOW_SetSimSpeed(float Multiplier) {}

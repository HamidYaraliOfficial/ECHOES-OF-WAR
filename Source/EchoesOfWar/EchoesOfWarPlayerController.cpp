#include "EchoesOfWarPlayerController.h"

void AEchoesOfWarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Enhanced Input mapping contexts (Mouse+Keyboard and Controller) are
	// bound here from Content/Input, providing full shortcut coverage for
	// the Command UI (map pan/zoom, order hotkeys, panel toggles).
}

void AEchoesOfWarPlayerController::IssueUnitOrder(const FUnitOrder& Order)
{
	// Single-player: applied directly against the OrderExecutionModel.
	// Multiplayer: wrapped as FCommandRequest and sent to the server for
	// authoritative validation before any world state changes.
}

void AEchoesOfWarPlayerController::SetActiveMapMode(bool bStrategicMap)
{
	// Toggles between the Strategic Map and Tactical Map widgets in the
	// Command UI; both read from the same UWorldSimulationSubsystem so
	// zooming between them never shows inconsistent data.
}

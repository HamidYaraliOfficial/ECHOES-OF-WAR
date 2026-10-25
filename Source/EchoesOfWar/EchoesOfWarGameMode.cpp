#include "EchoesOfWarGameMode.h"
#include "EchoesOfWarPlayerController.h"

AEchoesOfWarGameMode::AEchoesOfWarGameMode()
{
	PlayerControllerClass = AEchoesOfWarPlayerController::StaticClass();
}

void AEchoesOfWarGameMode::StartPlay()
{
	Super::StartPlay();
	// Campaign/scenario bootstrap (loading the selected UMapDataAsset,
	// registering factions/units/regions into the World Simulation
	// Subsystem) happens here, driven entirely by the data selected on the
	// Campaign Selection screen - no hard-coded scenario.
}

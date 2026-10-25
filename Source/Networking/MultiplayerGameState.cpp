#include "MultiplayerGameState.h"
#include "Net/UnrealNetwork.h"

void AMultiplayerGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMultiplayerGameState, ReplicatedSimDay);
	DOREPLIFETIME(AMultiplayerGameState, ActivePlayerFactions);
	DOREPLIFETIME(AMultiplayerGameState, SnapshotSequenceId);
}

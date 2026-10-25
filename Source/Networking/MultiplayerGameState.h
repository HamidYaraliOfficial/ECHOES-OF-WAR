#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CoreTypes.h"
#include "MultiplayerGameState.generated.h"

/**
 * Server-authoritative replicated game state for optional multiplayer
 * (Co-op Command or Competitive Faction Warfare). The simulation core in
 * the Simulation/AI/Units/etc modules stays completely independent of
 * networking; this class only mirrors the subset of world state clients
 * need to render, and relays player commands back to the server for
 * authoritative resolution.
 */
UCLASS()
class NETWORKING_API AMultiplayerGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Networking")
	int32 ReplicatedSimDay = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Networking")
	TArray<FFactionId> ActivePlayerFactions;

	/** Monotonically increasing snapshot id, used by clients for lag-compensated interpolation. */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Networking")
	int32 SnapshotSequenceId = 0;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

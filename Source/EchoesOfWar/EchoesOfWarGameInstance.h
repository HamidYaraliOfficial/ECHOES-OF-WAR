#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TimerManager.h"
#include "EchoesOfWarGameInstance.generated.h"

/**
 * Owns the central simulation clock. Deliberately decoupled from render
 * tick (Engine's Tick()): world/economy/logistics/AI advance on their own
 * fixed cadence via a timer, so a heavy simulation pass never causes a
 * dropped render frame, and the player-configurable simulation speed
 * (including day length and how often supply/resupply cycles run) is
 * exactly one place to change.
 */
UCLASS()
class ECHOESOFWAR_API UEchoesOfWarGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	/** Player-configurable: real seconds per simulated day. Exposed in Settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation Clock")
	float RealSecondsPerSimDay = 60.f;

	/** Player-configurable: how often (in sim days) automatic resupply convoys are dispatched. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation Clock")
	float ResupplyCycleDays = 1.f;

	UFUNCTION(BlueprintCallable, Category = "Simulation Clock")
	void SetSimulationSpeedMultiplier(float Multiplier);

	UFUNCTION(BlueprintCallable, Category = "Simulation Clock")
	void PauseSimulation(bool bPaused) { bSimulationPaused = bPaused; }

	/** Seconds remaining (real time) until the next full sim day advances - drives the UI's "next update in..." readout. */
	UFUNCTION(BlueprintPure, Category = "Simulation Clock")
	float GetSecondsUntilNextSimDay() const;

private:
	void OnSimTick();

	FTimerHandle SimTickHandle;
	float SimulationSpeedMultiplier = 1.f;
	bool bSimulationPaused = false;
	float AccumulatedRealSeconds = 0.f;
};

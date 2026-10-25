#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RegionState.h"
#include "WorldSimulationSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegionChanged, const FRegionId&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrontlineShifted, const FRegionId&);

/**
 * The World Simulation Engine.
 * Owns every FRegionState and advances the persistent world one simulation
 * "day" at a time (independent from render framerate - see TickAccumulator).
 * Every other system (Logistics, Economy, AI, Frontline, Events, UI) reads
 * region data from here rather than caching its own copy, so the world
 * always has a single source of truth.
 */
UCLASS()
class SIMULATION_API UWorldSimulationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Advance the world simulation by one in-game day. Called by the
	 *  central simulation clock, decoupled from render tick. */
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	void AdvanceOneSimDay();

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	void RegisterRegion(const FRegionState& InitialState);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	bool GetRegion(const FRegionId& Id, FRegionState& OutState) const;

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	void SetRegionController(const FRegionId& Id, const FFactionId& NewController);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	void ApplyWarDamage(const FRegionId& Id, float DamageAmount, EInfrastructureType TargetInfra);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	TArray<FRegionId> GetAllRegionIds() const;

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	TArray<FRegionId> GetRegionsControlledBy(const FFactionId& Faction) const;

	/** Sum of a faction's regional industrial capacity - feeds Economy module. */
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	float GetFactionIndustrialCapacity(const FFactionId& Faction) const;

	int32 GetCurrentSimDay() const { return CurrentSimDay; }

	FOnRegionChanged OnRegionChanged;
	FOnFrontlineShifted OnFrontlineShifted;

protected:
	void TickRegionEconomy(FRegionState& Region);
	void TickRegionPopulation(FRegionState& Region);
	void TickRegionStability(FRegionState& Region);
	void RecomputeFrontlineFlags();

	UPROPERTY()
	TMap<FRegionId, FRegionState> Regions;

	int32 CurrentSimDay = 0;
};

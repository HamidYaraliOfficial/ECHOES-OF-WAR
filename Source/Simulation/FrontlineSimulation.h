#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "WorldSimulationSubsystem.h"
#include "FrontlineSimulation.generated.h"

/** A contested segment of the frontline between two factions across one region. */
USTRUCT(BlueprintType)
struct SIMULATION_API FFrontlineSegment
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frontline")
	FRegionId Region;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frontline")
	FFactionId AttackingFaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frontline")
	FFactionId DefendingFaction;
	/** -1 = fully attacker controlled, +1 = fully defender controlled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frontline")
	float PressureBalance = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frontline")
	float AttackerCombatPower = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frontline")
	float DefenderCombatPower = 0.f;
};

/**
 * Frontlines are not a fixed drawn line: they emerge from where opposing
 * forces, supply, morale and terrain interact. This system recomputes
 * pressure every simulated day and can flip regional control when pressure
 * fully collapses to one side.
 */
UCLASS()
class SIMULATION_API UFrontlineSimulation : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Frontline")
	void UpdateSegment(UPARAM(ref) FFrontlineSegment& Segment, float TerrainDefenseBonus, float WeatherModifier, float DeltaDays);

	UFUNCTION(BlueprintCallable, Category = "Frontline")
	bool TryResolveCapture(const FFrontlineSegment& Segment, UWorldSimulationSubsystem* WorldSim);

	UPROPERTY()
	TArray<FFrontlineSegment> ActiveSegments;
};

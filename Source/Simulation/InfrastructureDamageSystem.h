#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "WorldSimulationSubsystem.h"
#include "InfrastructureDamageSystem.generated.h"

/** An active repair job being carried out by engineering units on a region's infrastructure. */
USTRUCT(BlueprintType)
struct SIMULATION_API FRepairJob
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Repair")
	FRegionId Region;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Repair")
	EInfrastructureType Target = EInfrastructureType::Road;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Repair")
	float EngineeringPointsAssigned = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Repair")
	float ProgressRemaining = 1.f; // 0 = complete
};

/**
 * Handles damage to roads, bridges, factories, power, comms and airports,
 * and the engineering effort required to bring them back online. Damaged
 * infrastructure directly throttles Logistics throughput and Economy output
 * via FRegionState::InfrastructureIntegrity.
 */
UCLASS()
class SIMULATION_API UInfrastructureDamageSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Infrastructure")
	void QueueRepair(const FRegionId& Region, EInfrastructureType Target, float EngineeringPoints);

	UFUNCTION(BlueprintCallable, Category = "Infrastructure")
	void TickRepairs(UWorldSimulationSubsystem* WorldSim, float DeltaDays);

	UPROPERTY()
	TArray<FRepairJob> ActiveJobs;
};

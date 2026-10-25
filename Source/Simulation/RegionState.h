#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "RegionState.generated.h"

/**
 * Full persistent state of a single simulated region (city, village, base,
 * industrial zone, resource node, ...). The WorldSimulationSubsystem owns
 * one of these per region and mutates it every simulation tick.
 * This is the beating heart of the "world is not just a set of fixed
 * missions" requirement: every number here can move, and everything else
 * in the game (logistics, morale, AI decisions, events) reads from it.
 */
USTRUCT(BlueprintType)
struct SIMULATION_API FRegionState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FRegionId Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FFactionId ControllingFaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	ETerrainType Terrain = ETerrainType::Plains;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FVector2D MapPosition = FVector2D::ZeroVector;

	// --- Population & society ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Population")
	int32 Population = 10000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Population")
	int32 DisplacedPopulation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Population")
	FNormalizedRating CivilianMorale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Population")
	FNormalizedRating Employment;

	// --- Political & security ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Politics")
	FNormalizedRating Loyalty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Politics")
	FNormalizedRating PoliticalStability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Security")
	FNormalizedRating Security;

	// --- Economy ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	float IndustrialCapacity = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	float ResourceOutputPerDay = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	float ResourceConsumptionPerDay = 8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	float LocalStockpile = 0.f;

	// --- Infrastructure & war damage ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infrastructure")
	TMap<EInfrastructureType, float> InfrastructureIntegrity; // 0..1 per type

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infrastructure")
	float AccumulatedWarDamage = 0.f;

	// --- Military ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Military")
	FNormalizedRating GarrisonStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Military")
	FNormalizedRating FrontPressure; // how hard this region is being contested

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Military")
	bool bIsFrontlineRegion = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Military")
	TArray<FRegionId> AdjacentRegions;

	float GetInfrastructureAverage() const
	{
		if (InfrastructureIntegrity.Num() == 0) return 1.f;
		float Sum = 0.f;
		for (const auto& Pair : InfrastructureIntegrity) Sum += Pair.Value;
		return Sum / InfrastructureIntegrity.Num();
	}
};

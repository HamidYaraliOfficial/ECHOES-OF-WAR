#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "OrderSystem.generated.h"

/** A single order issued to a unit, which may or may not be executed cleanly. */
USTRUCT(BlueprintType)
struct UNITS_API FUnitOrder
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	FUnitId TargetUnit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	EOrderType OrderType = EOrderType::Hold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	FRegionId TargetRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	float IssuedAtSimHour = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	bool bScheduled = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	float ScheduledForSimHour = 0.f;
};

/**
 * Orders are not guaranteed to execute perfectly: communication delay,
 * morale, suppression, fatigue, officer quality, terrain and damage can all
 * degrade or delay execution. This system computes the probability an order
 * is received cleanly and on time.
 */
UCLASS()
class UNITS_API UOrderExecutionModel : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Order")
	float ComputeExecutionProbability(float CommQuality, float UnitMorale, float Fatigue,
		float OfficerQuality, bool bUnderSuppression, bool bCommsDamaged) const;

	UFUNCTION(BlueprintCallable, Category = "Order")
	float ComputeCommunicationDelayHours(float CommQuality, float Distance) const;
};

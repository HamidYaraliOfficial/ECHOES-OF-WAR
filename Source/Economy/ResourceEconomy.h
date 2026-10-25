#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "ResourceEconomy.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Iron, Fuel, Electronics, Food, AmmoComponents, IndustrialCapacityPoints
};

/** A faction's national resource ledger. */
USTRUCT(BlueprintType)
struct ECONOMY_API FFactionEconomy
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	FFactionId Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	TMap<EResourceType, float> Stockpiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	TMap<EResourceType, float> DailyProduction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	TMap<EResourceType, float> DailyConsumption;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	float Budget = 0.f;
};

/**
 * National-level resource economy: iron/fuel/electronics/food/ammo
 * components/industrial capacity are produced by regions (see Simulation)
 * and consumed by units, production lines and civilian population. Running
 * a resource dry throttles whatever depends on it.
 */
UCLASS()
class ECONOMY_API UResourceEconomySystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Economy")
	void TickDay(UPARAM(ref) FFactionEconomy& Economy);

	UFUNCTION(BlueprintCallable, Category = "Economy")
	bool TrySpend(UPARAM(ref) FFactionEconomy& Economy, EResourceType Type, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Economy")
	float GetShortfall(const FFactionEconomy& Economy, EResourceType Type) const;
};

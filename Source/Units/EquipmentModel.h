#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "EquipmentModel.generated.h"

UENUM(BlueprintType)
enum class EEquipmentClass : uint8
{
	Vehicle, Weapon, Armor, Ammunition, Fuel, MedicalSupplies,
	SpareParts, DroneHardware, Sensor, CommsGear, EngineeringGear
};

/** A single equipment type's operating envelope. Values are abstract game
 *  balancing numbers, not real-world weapons data. */
USTRUCT(BlueprintType)
struct UNITS_API FEquipmentDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FName EquipmentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentClass Category = EEquipmentClass::Vehicle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (ClampMin = "0", ClampMax = "1"))
	float BaseReliability = 0.9f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float EffectiveRange = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (ClampMin = "0", ClampMax = "1"))
	float BaseAccuracy = 0.6f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float MobilityRating = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float MaintenanceCostPerDay = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float SupplyRequirementPerDay = 1.f;
};

/** A specific equipment item held by a unit, with wear tracked over time. */
USTRUCT(BlueprintType)
struct UNITS_API FEquipmentInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FName DefinitionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (ClampMin = "0", ClampMax = "1"))
	float Condition = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	int32 Quantity = 1;

	float GetEffectiveReliability(float BaseReliability) const
	{
		return FMath::Clamp(BaseReliability * (0.4f + 0.6f * Condition), 0.f, 1.f);
	}
};

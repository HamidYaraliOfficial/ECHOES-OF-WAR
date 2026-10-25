#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "ResourceEconomy.h"
#include "MilitaryIndustrySystem.generated.h"

UENUM(BlueprintType)
enum class EProductionOutputType : uint8
{
	Ammunition, Vehicles, Components, Drones, RepairParts, MedicalSupplies
};

/** A single factory: converts raw resources into finished military output. */
USTRUCT(BlueprintType)
struct ECONOMY_API FFactoryState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry")
	FName FactoryId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry")
	FRegionId HostRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry")
	EProductionOutputType OutputType = EProductionOutputType::Ammunition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry")
	float BaseOutputPerDay = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry")
	TMap<EResourceType, float> InputRequirementPerUnit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry", meta = (ClampMin = "0", ClampMax = "1"))
	float PowerAvailability = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry", meta = (ClampMin = "0", ClampMax = "1"))
	float LaborAvailability = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Industry", meta = (ClampMin = "0", ClampMax = "1"))
	float SecurityLevel = 1.f;
};

/**
 * Factories can only produce as much as their resource inputs, power, labor
 * and regional security allow - so bombing a power grid or destabilizing a
 * region genuinely throttles output, not just a UI number.
 */
UCLASS()
class ECONOMY_API UMilitaryIndustrySystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Industry")
	float ComputeActualOutput(const FFactoryState& Factory, UPARAM(ref) FFactionEconomy& Economy);

	UFUNCTION(BlueprintCallable, Category = "Industry")
	void RelocateFactory(UPARAM(ref) FFactoryState& Factory, const FRegionId& NewRegion, float DisruptionDays);
};

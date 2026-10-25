#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "MedicalRecoverySystem.generated.h"

/** A field hospital / medical facility with limited treatment capacity. */
USTRUCT(BlueprintType)
struct UNITS_API FMedicalFacility
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Medical")
	FRegionId HostRegion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Medical")
	int32 BedCapacity = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Medical")
	int32 PatientsInTreatment = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Medical")
	int32 UpgradeLevel = 1;

	float GetAvailableCapacityRatio() const
	{
		return BedCapacity > 0 ? 1.f - (float)PatientsInTreatment / (float)BedCapacity : 0.f;
	}
};

/**
 * Wounded personnel are transferred to facilities with finite capacity;
 * overflow patients wait and recover more slowly / risk being lost.
 * Casualty management here feeds directly back into unit CurrentStrength.
 */
UCLASS()
class UNITS_API UMedicalRecoverySystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Medical")
	int32 AdmitWounded(UPARAM(ref) FMedicalFacility& Facility, int32 WoundedCount);

	UFUNCTION(BlueprintCallable, Category = "Medical")
	int32 ProcessRecoveryTick(UPARAM(ref) FMedicalFacility& Facility, float DeltaDays);

	UFUNCTION(BlueprintCallable, Category = "Medical")
	void UpgradeFacility(UPARAM(ref) FMedicalFacility& Facility);
};

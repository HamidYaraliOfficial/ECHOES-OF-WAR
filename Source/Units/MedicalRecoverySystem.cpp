#include "MedicalRecoverySystem.h"

int32 UMedicalRecoverySystem::AdmitWounded(FMedicalFacility& Facility, int32 WoundedCount)
{
	const int32 FreeBeds = FMath::Max(0, Facility.BedCapacity - Facility.PatientsInTreatment);
	const int32 Admitted = FMath::Min(FreeBeds, WoundedCount);
	Facility.PatientsInTreatment += Admitted;
	return WoundedCount - Admitted; // overflow, left untreated this tick
}

int32 UMedicalRecoverySystem::ProcessRecoveryTick(FMedicalFacility& Facility, float DeltaDays)
{
	const float RecoveryRatePerPatient = 0.1f * (1.f + Facility.UpgradeLevel * 0.2f);
	const int32 Recovered = FMath::Min(Facility.PatientsInTreatment,
		FMath::RoundToInt(Facility.PatientsInTreatment * RecoveryRatePerPatient * DeltaDays));
	Facility.PatientsInTreatment -= Recovered;
	return Recovered; // returned to duty
}

void UMedicalRecoverySystem::UpgradeFacility(FMedicalFacility& Facility)
{
	Facility.UpgradeLevel++;
	Facility.BedCapacity = FMath::RoundToInt(Facility.BedCapacity * 1.4f);
}

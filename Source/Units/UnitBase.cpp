#include "UnitBase.h"

void UUnitStateLibrary::ApplyCasualties(FPersistentUnitState& Unit, int32 Casualties)
{
	Casualties = FMath::Clamp(Casualties, 0, Unit.CurrentStrength);
	Unit.CurrentStrength -= Casualties;
	Unit.TotalCasualtiesSuffered += Casualties;

	const float LossRatio = Unit.AuthorizedStrength > 0 ? (float)Casualties / (float)Unit.AuthorizedStrength : 0.f;
	Unit.Morale.Add(-LossRatio * 1.5f);
	Unit.Fatigue = FMath::Clamp(Unit.Fatigue + LossRatio, 0.f, 1.f);
}

void UUnitStateLibrary::GrantExperience(FPersistentUnitState& Unit, float Amount)
{
	Unit.Experience = FMath::Clamp(Unit.Experience + Amount, 0.f, 1.f);
}

void UUnitStateLibrary::ApplyRestAndResupply(FPersistentUnitState& Unit, float RestHours, float SupplyDelivered)
{
	Unit.Fatigue = FMath::Clamp(Unit.Fatigue - RestHours * 0.02f, 0.f, 1.f);
	Unit.Morale.Add(RestHours * 0.005f);
	Unit.SupplyStatus = FMath::Clamp(Unit.SupplyStatus + SupplyDelivered, 0.f, 1.f);
}

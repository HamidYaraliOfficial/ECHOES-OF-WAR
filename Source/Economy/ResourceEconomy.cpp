#include "ResourceEconomy.h"

void UResourceEconomySystem::TickDay(FFactionEconomy& Economy)
{
	for (auto& Pair : Economy.DailyProduction)
	{
		float& Stock = Economy.Stockpiles.FindOrAdd(Pair.Key, 0.f);
		Stock += Pair.Value;
	}
	for (auto& Pair : Economy.DailyConsumption)
	{
		float& Stock = Economy.Stockpiles.FindOrAdd(Pair.Key, 0.f);
		Stock = FMath::Max(0.f, Stock - Pair.Value);
	}
}

bool UResourceEconomySystem::TrySpend(FFactionEconomy& Economy, EResourceType Type, float Amount)
{
	float& Stock = Economy.Stockpiles.FindOrAdd(Type, 0.f);
	if (Stock < Amount) return false;
	Stock -= Amount;
	return true;
}

float UResourceEconomySystem::GetShortfall(const FFactionEconomy& Economy, EResourceType Type) const
{
	const float Production = Economy.DailyProduction.Contains(Type) ? Economy.DailyProduction[Type] : 0.f;
	const float Consumption = Economy.DailyConsumption.Contains(Type) ? Economy.DailyConsumption[Type] : 0.f;
	return FMath::Max(0.f, Consumption - Production);
}

#include "WeatherSystem.h"

void UWeatherSystem::TickWeather(FWeatherState& State, float DeltaHours)
{
	State.HoursRemaining -= DeltaHours;
	if (State.HoursRemaining <= 0.f)
	{
		State.CurrentWeather = RollNextWeather(ETerrainType::Plains);
		State.HoursRemaining = FMath::FRandRange(4.f, 18.f);
	}
}

void UWeatherSystem::ForceWeather(FWeatherState& State, EWeatherType NewWeather, float DurationHours)
{
	State.CurrentWeather = NewWeather;
	State.HoursRemaining = DurationHours;
}

EWeatherType UWeatherSystem::RollNextWeather(ETerrainType RegionTerrain) const
{
	const float Roll = FMath::FRand();
	if (RegionTerrain == ETerrainType::Desert)
	{
		if (Roll < 0.15f) return EWeatherType::Sandstorm;
		if (Roll < 0.3f) return EWeatherType::HeatWave;
		return EWeatherType::Clear;
	}
	if (Roll < 0.35f) return EWeatherType::Clear;
	if (Roll < 0.55f) return EWeatherType::Rain;
	if (Roll < 0.65f) return EWeatherType::Fog;
	if (Roll < 0.8f) return EWeatherType::Storm;
	if (Roll < 0.92f) return EWeatherType::Snow;
	return EWeatherType::Clear;
}

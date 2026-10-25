#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "WeatherSystem.generated.h"

/** Per-region weather state and its gameplay modifiers. */
USTRUCT(BlueprintType)
struct SIMULATION_API FWeatherState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	EWeatherType CurrentWeather = EWeatherType::Clear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	float HoursRemaining = 6.f;

	/** Multiplier applied to unit movement speed. */
	float GetMovementModifier() const
	{
		switch (CurrentWeather)
		{
			case EWeatherType::Rain: return 0.85f;
			case EWeatherType::Storm: return 0.55f;
			case EWeatherType::Fog: return 0.9f;
			case EWeatherType::Snow: return 0.65f;
			case EWeatherType::Sandstorm: return 0.5f;
			case EWeatherType::HeatWave: return 0.9f;
			default: return 1.0f;
		}
	}

	/** Multiplier applied to visibility / detection range. */
	float GetVisibilityModifier() const
	{
		switch (CurrentWeather)
		{
			case EWeatherType::Fog: return 0.3f;
			case EWeatherType::Storm: return 0.5f;
			case EWeatherType::Sandstorm: return 0.25f;
			case EWeatherType::Snow: return 0.7f;
			default: return 1.0f;
		}
	}

	/** Multiplier applied to supply-route throughput. */
	float GetLogisticsModifier() const
	{
		switch (CurrentWeather)
		{
			case EWeatherType::Storm: return 0.4f;
			case EWeatherType::Snow: return 0.6f;
			case EWeatherType::Sandstorm: return 0.5f;
			default: return 1.0f;
		}
	}
};

UCLASS()
class SIMULATION_API UWeatherSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Weather")
	void TickWeather(UPARAM(ref) FWeatherState& State, float DeltaHours);

	UFUNCTION(BlueprintCallable, Category = "Weather")
	void ForceWeather(UPARAM(ref) FWeatherState& State, EWeatherType NewWeather, float DurationHours);

private:
	EWeatherType RollNextWeather(ETerrainType RegionTerrain) const;
};

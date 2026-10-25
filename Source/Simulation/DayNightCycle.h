#pragma once
#include "CoreMinimal.h"
#include "DayNightCycle.generated.h"

/**
 * Tracks in-game time of day and the day/night boundary. Night reduces
 * detection range and lowers movement/attack precision for units without
 * night-vision equipment (queried by Combat/Intelligence systems).
 */
UCLASS()
class SIMULATION_API UDayNightCycle : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Time")
	void Advance(float DeltaHours);

	UFUNCTION(BlueprintPure, Category = "Time")
	bool IsNight() const { return HourOfDay < SunriseHour || HourOfDay >= SunsetHour; }

	UFUNCTION(BlueprintPure, Category = "Time")
	float GetVisibilityModifier() const { return IsNight() ? 0.4f : 1.0f; }

	UFUNCTION(BlueprintPure, Category = "Time")
	float GetHourOfDay() const { return HourOfDay; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float SunriseHour = 6.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float SunsetHour = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int32 DayCount = 0;

private:
	UPROPERTY(VisibleAnywhere, Category = "Time")
	float HourOfDay = 6.f;
};

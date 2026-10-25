#include "DayNightCycle.h"

void UDayNightCycle::Advance(float DeltaHours)
{
	HourOfDay += DeltaHours;
	while (HourOfDay >= 24.f)
	{
		HourOfDay -= 24.f;
		DayCount++;
	}
}

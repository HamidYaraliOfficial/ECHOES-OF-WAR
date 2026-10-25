#include "EchoesOfWarGameInstance.h"
#include "WorldSimulationSubsystem.h"

void UEchoesOfWarGameInstance::Init()
{
	Super::Init();
	// Ticks frequently (10x/sec) purely to accumulate real time; the actual
	// AdvanceOneSimDay() call only fires once AccumulatedRealSeconds crosses
	// RealSecondsPerSimDay, keeping the heavy simulation pass rare and
	// entirely decoupled from render/UI framerate.
	GetTimerManager().SetTimer(SimTickHandle, this, &UEchoesOfWarGameInstance::OnSimTick, 0.1f, true);
}

void UEchoesOfWarGameInstance::Shutdown()
{
	GetTimerManager().ClearTimer(SimTickHandle);
	Super::Shutdown();
}

void UEchoesOfWarGameInstance::SetSimulationSpeedMultiplier(float Multiplier)
{
	SimulationSpeedMultiplier = FMath::Clamp(Multiplier, 0.f, 8.f);
}

float UEchoesOfWarGameInstance::GetSecondsUntilNextSimDay() const
{
	return FMath::Max(0.f, RealSecondsPerSimDay - AccumulatedRealSeconds);
}

void UEchoesOfWarGameInstance::OnSimTick()
{
	if (bSimulationPaused) return;

	AccumulatedRealSeconds += 0.1f * SimulationSpeedMultiplier;
	if (AccumulatedRealSeconds >= RealSecondsPerSimDay)
	{
		AccumulatedRealSeconds -= RealSecondsPerSimDay;
		if (UWorldSimulationSubsystem* WorldSim = GetSubsystem<UWorldSimulationSubsystem>())
		{
			WorldSim->AdvanceOneSimDay();
		}
	}
}

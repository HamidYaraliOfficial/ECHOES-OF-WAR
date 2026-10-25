#include "CommunicationNetwork.h"

void UCommunicationNetwork::RegisterRelay(const FCommRelayNode& Relay)
{
	Relays.Add(Relay);
}

float UCommunicationNetwork::GetCoverageQuality(const FVector2D& UnitPosition, const TMap<FRegionId, FVector2D>& RegionPositions) const
{
	float BestQuality = 0.f;
	for (const FCommRelayNode& Relay : Relays)
	{
		if (const FVector2D* Pos = RegionPositions.Find(Relay.HostRegion))
		{
			const float Distance = FVector2D::Distance(*Pos, UnitPosition);
			if (Distance <= Relay.CoverageRadius)
			{
				const float FalloffQuality = Relay.Integrity * (1.f - Distance / Relay.CoverageRadius);
				BestQuality = FMath::Max(BestQuality, FalloffQuality);
			}
		}
	}
	return FMath::Clamp(BestQuality, 0.f, 1.f);
}

#include "SaveGameSystem.h"
#include "Misc/SecureHash.h"

FString USaveGameSystem::ComputeChecksum(const UCampaignSaveData* SaveData) const
{
	if (!SaveData) return FString();

	FString Combined = FString::Printf(TEXT("%d|%s|%d"),
		SaveData->SaveFormatVersion, *SaveData->ScenarioId, SaveData->CurrentSimDay);

	TArray<FString> Keys;
	SaveData->SubsystemBlobsJson.GetKeys(Keys);
	Keys.Sort();
	for (const FString& Key : Keys)
	{
		Combined += TEXT("|") + Key + TEXT("=") + SaveData->SubsystemBlobsJson[Key];
	}

	return FMD5::HashAnsiString(*Combined);
}

bool USaveGameSystem::ValidateIntegrity(const UCampaignSaveData* SaveData) const
{
	if (!SaveData) return false;
	return ComputeChecksum(SaveData) == SaveData->IntegrityChecksum;
}

bool USaveGameSystem::MigrateToCurrentVersion(UCampaignSaveData* SaveData, int32 TargetVersion)
{
	if (!SaveData) return false;

	// Each step below would translate exactly one version bump; kept as an
	// explicit, auditable chain rather than a single "best effort" jump.
	while (SaveData->SaveFormatVersion < TargetVersion)
	{
		switch (SaveData->SaveFormatVersion)
		{
			// case 1: /* migrate v1 -> v2 fields here when introduced */ break;
			default:
				return false; // no known migration path - refuse rather than corrupt data
		}
		SaveData->SaveFormatVersion++;
	}
	return true;
}

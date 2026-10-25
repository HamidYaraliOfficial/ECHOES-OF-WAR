#include "Misc/AutomationTest.h"
#include "SaveGameSystem.h"
#include "CampaignSaveData.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSaveChecksumDetectsTamperingTest, "EchoesOfWar.Save.ChecksumDetectsTampering",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSaveChecksumDetectsTamperingTest::RunTest(const FString& Parameters)
{
	USaveGameSystem* SaveSystem = NewObject<USaveGameSystem>();
	UCampaignSaveData* SaveData = NewObject<UCampaignSaveData>();
	SaveData->ScenarioId = TEXT("Scenario_001");
	SaveData->CurrentSimDay = 42;
	SaveData->SubsystemBlobsJson.Add(TEXT("WorldSim"), TEXT("{\"regions\":[]}"));
	SaveData->IntegrityChecksum = SaveSystem->ComputeChecksum(SaveData);

	TestTrue(TEXT("Freshly-checksummed save must validate"), SaveSystem->ValidateIntegrity(SaveData));

	SaveData->CurrentSimDay = 43; // simulate corruption/tampering after checksum was written
	TestFalse(TEXT("Mutated save data must fail integrity validation"), SaveSystem->ValidateIntegrity(SaveData));

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS

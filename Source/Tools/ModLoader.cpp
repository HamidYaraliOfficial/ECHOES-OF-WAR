#include "ModLoader.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool UModLoader::ParseManifestJson(const FString& JsonText, FModManifest& OutManifest) const
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		return false;
	}

	OutManifest.ModId = JsonObject->GetStringField(TEXT("modId"));
	OutManifest.DisplayName = JsonObject->GetStringField(TEXT("displayName"));
	OutManifest.Author = JsonObject->GetStringField(TEXT("author"));
	OutManifest.TargetGameVersion = JsonObject->GetStringField(TEXT("targetGameVersion"));

	const TArray<TSharedPtr<FJsonValue>>* DataFilesArray;
	if (JsonObject->TryGetArrayField(TEXT("dataFiles"), DataFilesArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : *DataFilesArray)
		{
			OutManifest.DataFiles.Add(Value->AsString());
		}
	}
	return true;
}

bool UModLoader::IsCompatible(const FModManifest& Manifest, const FString& CurrentGameVersion) const
{
	return Manifest.TargetGameVersion == CurrentGameVersion;
}

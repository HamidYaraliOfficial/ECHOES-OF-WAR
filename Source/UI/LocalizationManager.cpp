#include "LocalizationManager.h"

void ULocalizationManager::LoadLanguageTable(EUILanguage Language, const TMap<FString, FString>& KeyToText)
{
	Tables.Add(Language, KeyToText);
}

void ULocalizationManager::SetActiveLanguage(EUILanguage Language)
{
	ActiveLanguage = Language;
}

FText ULocalizationManager::Resolve(const FString& Key, const TMap<FString, FString>& Params) const
{
	FString Result = Key;
	if (const TMap<FString, FString>* Table = Tables.Find(ActiveLanguage))
	{
		if (const FString* Found = Table->Find(Key))
		{
			Result = *Found;
		}
	}

	for (const auto& Param : Params)
	{
		Result = Result.Replace(*FString::Printf(TEXT("{%s}"), *Param.Key), *Param.Value);
	}

	return FText::FromString(Result);
}

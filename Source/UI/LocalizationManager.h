#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "LocalizationManager.generated.h"

/**
 * Runtime language switching for English / Persian / Chinese, with correct
 * text direction per language (Persian is RTL, English and Chinese are
 * LTR). All UI, tutorial, tooltip, report and subtitle text is looked up
 * through here by key rather than hard-coded, and font fallback ensures
 * Latin, Perso-Arabic and CJK glyphs all render correctly regardless of
 * which language is active.
 */
UCLASS()
class UI_API ULocalizationManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Localization")
	void LoadLanguageTable(EUILanguage Language, const TMap<FString, FString>& KeyToText);

	UFUNCTION(BlueprintCallable, Category = "Localization")
	void SetActiveLanguage(EUILanguage Language);

	UFUNCTION(BlueprintCallable, Category = "Localization")
	FText Resolve(const FString& Key, const TMap<FString, FString>& Params) const;

	UFUNCTION(BlueprintPure, Category = "Localization")
	ETextDirection GetActiveDirection() const { return GetDirectionFor(ActiveLanguage); }

	UFUNCTION(BlueprintPure, Category = "Localization")
	static ETextDirection GetDirectionFor(EUILanguage Language)
	{
		return Language == EUILanguage::Persian ? ETextDirection::RightToLeft : ETextDirection::LeftToRight;
	}

	UFUNCTION(BlueprintPure, Category = "Localization")
	static FString GetPreferredFontFace(EUILanguage Language)
	{
		switch (Language)
		{
			case EUILanguage::Persian: return TEXT("Vazirmatn");     // Perso-Arabic, full RTL shaping
			case EUILanguage::Chinese: return TEXT("NotoSansSC");    // CJK coverage
			default: return TEXT("Inter");                          // Latin UI font
		}
	}

	EUILanguage GetActiveLanguage() const { return ActiveLanguage; }

private:
	UPROPERTY()
	TMap<EUILanguage, FString> SerializedTables; // JSON blob per language, see Content/Localization/*.json
	TMap<EUILanguage, TMap<FString, FString>> Tables;
	EUILanguage ActiveLanguage = EUILanguage::English;
};

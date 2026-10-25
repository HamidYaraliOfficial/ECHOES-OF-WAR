#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "UIThemeManager.generated.h"

/** Full color/style palette for one selectable UI theme. */
USTRUCT(BlueprintType)
struct UI_API FUIThemePalette
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	EUITheme Theme = EUITheme::Windows11;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	FLinearColor BackgroundPrimary = FLinearColor(0.098f, 0.098f, 0.098f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	FLinearColor BackgroundSecondary = FLinearColor(0.145f, 0.145f, 0.145f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	FLinearColor AccentColor = FLinearColor(0.f, 0.47f, 0.843f); // Windows 11 blue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	FLinearColor TextPrimary = FLinearColor(0.95f, 0.95f, 0.95f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	FLinearColor TextSecondary = FLinearColor(0.7f, 0.7f, 0.7f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	FLinearColor WarningColor = FLinearColor(0.92f, 0.65f, 0.05f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	FLinearColor CriticalColor = FLinearColor(0.85f, 0.15f, 0.15f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	float CornerRadius = 6.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theme")
	bool bUseAcrylicBlur = true; // Windows-11-style translucent panels
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnThemeChanged, EUITheme);

/**
 * Central theme registry driving every widget's palette. Ships with six
 * built-in themes: Windows 11 (default, acrylic + rounded corners), Light,
 * Dark, High Contrast (accessibility), Blue Command and Red Alert. Also
 * tracks whether the OS-reported theme should be followed automatically.
 */
UCLASS()
class UI_API UUIThemeManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Theme")
	void InitializeDefaultThemes();

	UFUNCTION(BlueprintCallable, Category = "Theme")
	void SetActiveTheme(EUITheme NewTheme);

	UFUNCTION(BlueprintCallable, Category = "Theme")
	FUIThemePalette GetActivePalette() const;

	UFUNCTION(BlueprintCallable, Category = "Theme")
	void SetFollowSystemTheme(bool bFollow) { bFollowSystemTheme = bFollow; }

	FOnThemeChanged OnThemeChanged;

private:
	UPROPERTY()
	TMap<EUITheme, FUIThemePalette> Palettes;
	EUITheme ActiveTheme = EUITheme::Windows11;
	bool bFollowSystemTheme = true;
};

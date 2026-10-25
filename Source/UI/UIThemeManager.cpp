#include "UIThemeManager.h"

void UUIThemeManager::InitializeDefaultThemes()
{
	Palettes.Empty();

	FUIThemePalette Win11;
	Win11.Theme = EUITheme::Windows11;
	Win11.BackgroundPrimary = FLinearColor(0.106f, 0.106f, 0.106f);
	Win11.AccentColor = FLinearColor(0.f, 0.47f, 0.843f);
	Win11.bUseAcrylicBlur = true;
	Palettes.Add(EUITheme::Windows11, Win11);

	FUIThemePalette Light;
	Light.Theme = EUITheme::Light;
	Light.BackgroundPrimary = FLinearColor(0.96f, 0.96f, 0.96f);
	Light.BackgroundSecondary = FLinearColor(0.88f, 0.88f, 0.88f);
	Light.TextPrimary = FLinearColor(0.08f, 0.08f, 0.08f);
	Light.TextSecondary = FLinearColor(0.3f, 0.3f, 0.3f);
	Light.AccentColor = FLinearColor(0.f, 0.4f, 0.75f);
	Light.bUseAcrylicBlur = false;
	Palettes.Add(EUITheme::Light, Light);

	FUIThemePalette Dark;
	Dark.Theme = EUITheme::Dark;
	Dark.BackgroundPrimary = FLinearColor(0.05f, 0.05f, 0.06f);
	Dark.BackgroundSecondary = FLinearColor(0.09f, 0.09f, 0.1f);
	Dark.AccentColor = FLinearColor(0.35f, 0.6f, 0.95f);
	Palettes.Add(EUITheme::Dark, Dark);

	FUIThemePalette HighContrast;
	HighContrast.Theme = EUITheme::HighContrast;
	HighContrast.BackgroundPrimary = FLinearColor(0.f, 0.f, 0.f);
	HighContrast.TextPrimary = FLinearColor(1.f, 1.f, 1.f);
	HighContrast.AccentColor = FLinearColor(1.f, 0.9f, 0.f);
	HighContrast.bUseAcrylicBlur = false;
	Palettes.Add(EUITheme::HighContrast, HighContrast);

	FUIThemePalette BlueCommand;
	BlueCommand.Theme = EUITheme::BlueCommand;
	BlueCommand.BackgroundPrimary = FLinearColor(0.03f, 0.06f, 0.12f);
	BlueCommand.BackgroundSecondary = FLinearColor(0.06f, 0.1f, 0.18f);
	BlueCommand.AccentColor = FLinearColor(0.15f, 0.55f, 0.95f);
	Palettes.Add(EUITheme::BlueCommand, BlueCommand);

	FUIThemePalette RedAlert;
	RedAlert.Theme = EUITheme::RedAlert;
	RedAlert.BackgroundPrimary = FLinearColor(0.1f, 0.02f, 0.02f);
	RedAlert.BackgroundSecondary = FLinearColor(0.16f, 0.04f, 0.04f);
	RedAlert.AccentColor = FLinearColor(0.85f, 0.15f, 0.15f);
	RedAlert.WarningColor = FLinearColor(0.95f, 0.5f, 0.05f);
	Palettes.Add(EUITheme::RedAlert, RedAlert);

	ActiveTheme = EUITheme::Windows11;
}

void UUIThemeManager::SetActiveTheme(EUITheme NewTheme)
{
	ActiveTheme = NewTheme;
	OnThemeChanged.Broadcast(ActiveTheme);
}

FUIThemePalette UUIThemeManager::GetActivePalette() const
{
	if (const FUIThemePalette* Palette = Palettes.Find(ActiveTheme))
	{
		return *Palette;
	}
	return FUIThemePalette();
}

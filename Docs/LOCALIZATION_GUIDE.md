# ECHOES OF WAR — Localization Guide

## Supported Languages
English (`en`, LTR), Persian (`fa`, **RTL**), Chinese Simplified (`zh`,
LTR). `ULocalizationManager::GetDirectionFor` is the single source of
truth for direction — UI layout code should query it rather than hard-
coding per-language assumptions.

## String Tables
Each language has a flat `key -> string` JSON table under
`Content/Localization/<lang>/ui_strings.json`. Keys are stable identifiers
(`"panel.logistics.title"`, `"news.region_captured"`); values may contain
`{paramName}` placeholders resolved by `ULocalizationManager::Resolve`.

## Adding a New String
1. Add the key to **all three** language files with an equivalent
   translation — `UContentValidationTool::ValidateLocalizationCoverage`
   flags any key missing from a language table.
2. Reference the key from gameplay/UI code via
   `LocalizationManager->Resolve(Key, Params)` — never hard-code display
   text in a widget.

## Fonts & Fallback
`ULocalizationManager::GetPreferredFontFace` maps each language to a font
family with full glyph coverage for that script (Perso-Arabic for Persian,
CJK for Chinese, Latin otherwise). Configure these as fallback fonts on
your UMG font assets so mixed-script strings (e.g. a Latin unit
designation inside a Persian sentence) still render correctly.

## RTL Layout Rules for UI Artists
- Mirror horizontal layouts (panel order, icon+label order, progress bar
  fill direction) when `GetActiveDirection() == RightToLeft`.
- Do **not** mirror numerals, map imagery, or icons that have inherent
  left/right meaning (e.g. a compass rose).
- Text alignment should follow direction (right-aligned body text in
  Persian, left-aligned in English/Chinese).

## Adding a New Language
Add a new `EUILanguage` enum entry (`CoreTypes.h`), a new
`Content/Localization/<lang>/ui_strings.json` covering every existing key,
and extend `GetDirectionFor` / `GetPreferredFontFace` for the new
language's direction and font needs.

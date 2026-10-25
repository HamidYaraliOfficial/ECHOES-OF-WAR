# ECHOES OF WAR — Modding Guide

## What Can Be Modded Without Touching C++
Everything under `Content/Data/` is data-driven JSON, loaded by
`UModLoader` (Tools module): factions, doctrines, unit templates,
technology nodes, scenarios, and (via `UMapDataAsset`) full maps —
settlements, infrastructure links, resource nodes, terrain features.

## Mod Folder Layout
```
Mods/<YourModId>/
  mod.json
  Data/
    factions.json
    units.json
    technology.json
    doctrines.json
    scenarios/<your_scenario>.json
  Localization/
    en/ui_strings.json
    fa/ui_strings.json
    zh/ui_strings.json
```

## mod.json
```json
{
  "modId": "your_mod_id",
  "displayName": "Your Mod Name",
  "author": "Your Name",
  "targetGameVersion": "0.1.0",
  "dataFiles": ["Data/factions.json", "Data/units.json"]
}
```
`UModLoader::ParseManifestJson` reads this; `IsCompatible` refuses to load
a mod whose `targetGameVersion` does not match the running game, so an
outdated mod fails loudly instead of corrupting a campaign silently.

## Adding a New Faction
Add an entry to your mod's `factions.json` following the shape in
`Content/Data/Factions/factions.json`, and a matching `doctrineId` in
`doctrines.json`. Reference your new `factionId` from any scenario's
`playableFactions` / `aiFactions` arrays.

## Adding a New Event
Register a `FDynamicEventDefinition` (Simulation module) with concrete
`FEventCondition`s — every condition is checked against real
`FRegionState` data (`UDynamicEventEngine::EvaluateCondition`), so an event
can never fire with no grounding in world state.

## Validating Your Mod
Run `UContentValidationTool::ValidateMap` and
`ValidateLocalizationCoverage` (Tools module, editor-only) against your
content before shipping a mod — it catches missing references, duplicate
ids, broken scenarios and missing localization keys.

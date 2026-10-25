# ECHOES OF WAR — Troubleshooting

## "Missing SDK" / "Windows SDK not found"
Reinstall via Visual Studio Installer → Individual Components → search
"Windows 10 SDK" or "Windows 11 SDK" → install, then re-run
`Scripts\setup-windows.ps1`.

## "Could not find compiler toolchain" / MSVC not found
Open Visual Studio Installer → Modify → confirm the **Game development
with C++** workload is checked (this pulls in the MSVC v143 toolset). If
you have multiple VS versions installed, delete `Intermediate\` and
`Binaries\` and regenerate project files.

## Plugin Issues on Open ("plugin failed to load")
Delete `Intermediate\` and `Saved\`, then right-click the `.uproject` →
**Generate Visual Studio project files** again. If a specific plugin
(listed in `EchoesOfWar.uproject` → `"Plugins"`) is genuinely missing from
your engine install, enable it from Epic Games Launcher → Engine
Installation → Options, or remove the plugin entry if you don't need it.

## Build Cache Corruption / Weird Incremental Build Errors
```powershell
Remove-Item -Recurse -Force .\Intermediate, .\Binaries, .\DerivedDataCache
```
Then rebuild from scratch.

## Redirector Warnings in Content Browser
Right-click the affected folder in Content Browser → **Fix Up Redirectors
in Folder**. This is expected after renaming/moving assets and is safe to
run any time.

## Packaging Error: "Cook Failed"
Check `Saved\Logs\` for the specific asset/reference that failed to cook.
Most commonly this is a `UMapDataAsset` or map referencing an asset path
that no longer exists — run `UContentValidationTool::ValidateMap` first.

## Automation Tests Don't Appear
Confirm the `Tests` module is listed in `EchoesOfWar.uproject`'s
`"Modules"` array and in `ExtraModuleNames` for the Editor target, then
regenerate project files and rebuild.

## Persian Text Renders Left-to-Right / Disconnected Letters
Confirm the font asset assigned in UMG has Persian/Arabic script shaping
enabled and that the widget's flow direction is bound to
`ULocalizationManager::GetActiveDirection()` rather than a hard-coded
`LeftToRight`.

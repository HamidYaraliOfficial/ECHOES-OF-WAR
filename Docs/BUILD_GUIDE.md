# ECHOES OF WAR — Build Guide

## Prerequisites
See `INSTALLATION.md` for full step-by-step setup. Summary: Unreal Engine
5.4+, Visual Studio 2022 with "Game development with C++", Windows 10/11
SDK, Git.

## First-Time Setup
```powershell
git init
.\Scripts\setup-windows.ps1
```
Then right-click `EchoesOfWar.uproject` → **Generate Visual Studio project
files**, and open the generated `.sln`.

## Development Build (Editor)
```powershell
.\Scripts\build-development.ps1
```
Or from Visual Studio: select the `EchoesOfWarEditor` target,
`Development Editor | Win64`, and build.

## Running the Editor
```powershell
& "C:\Program Files\Epic Games\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe" "<path-to>\EchoesOfWar.uproject"
```

## Running Automation Tests
```powershell
.\Scripts\run-tests.ps1
```

## Shipping Package
```powershell
.\Scripts\build-shipping.ps1
```
Output lands under `Build\Shipping\` by default (`-OutputDir` to change).

## One-Shot Pipeline
```powershell
.\Scripts\package.ps1
```
Runs tests → development build → shipping package, stopping at the first
failure — this is the same sequence a CI job should run.

## Registering New Modules
If you add a `Source/<NewModule>` folder: create its `.Build.cs`, add it to
the `"Modules"` array in `EchoesOfWar.uproject`, and add its name to
`ExtraModuleNames` in both `EchoesOfWar.Target.cs` and
`EchoesOfWarEditor.Target.cs`.

# ECHOES OF WAR — Installation (Windows)

## 1. Install Git
Download and install from https://git-scm.com/download/win (default
options are fine). Verify:
```powershell
git --version
```

## 2. Install Visual Studio 2022
Download the Community, Professional or Enterprise installer from
https://visualstudio.microsoft.com/vs/ and, in the Workloads tab, check:
- **Game development with C++**
- (Individual Components tab) **Windows 10 SDK** or **Windows 11 SDK**,
  whichever matches your OS
- (Individual Components tab) **C++ profiling tools** (optional but
  recommended)

## 3. Install Unreal Engine 5
Install the Epic Games Launcher, sign in, go to the **Unreal Engine** tab
→ **Library**, and install **5.4** or later. Note the install path (default
`C:\Program Files\Epic Games\UE_5.4`) — the PowerShell scripts in
`Scripts\` default to this path and take `-EnginePath` if yours differs.

## 4. (Optional) CMake
Only needed if you add a third-party C++ library with its own CMake build.
Install from https://cmake.org/download/ if/when that becomes necessary;
the project itself does not require it out of the box.

## 5. Verify Your Environment
```powershell
cd EchoesOfWar
.\Scripts\setup-windows.ps1
```
Fix anything reported as `[MISSING]` before continuing.

## 6. Open the Project
Right-click `EchoesOfWar.uproject` → **Generate Visual Studio project
files**. Then either:
- Double-click `EchoesOfWar.uproject` to open directly in the Editor
  (it will offer to compile missing modules automatically), or
- Open the generated `.sln` in Visual Studio 2022, set the startup project
  to `EchoesOfWar`, configuration `Development Editor | Win64`, and press
  **Start** (F5).

## 7. Compile the C++ Modules
From Visual Studio: **Build → Build Solution** (Ctrl+Shift+B).
From PowerShell instead:
```powershell
.\Scripts\build-development.ps1
```

## 8. Run the Editor
```powershell
& "C:\Program Files\Epic Games\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe" "$(Resolve-Path .\EchoesOfWar.uproject)"
```

## 9. Run Automation Tests
```powershell
.\Scripts\run-tests.ps1
```

## 10. Build a Development Package
```powershell
.\Scripts\build-development.ps1
```

## 11. Build a Shipping Package
```powershell
.\Scripts\build-shipping.ps1
```
Packaged output appears under `Build\Shipping\` by default.

## Common Errors
See `Docs\TROUBLESHOOTING.md` for Missing SDK, compiler toolchain, plugin,
build cache, redirector and packaging errors, with fixes for each.

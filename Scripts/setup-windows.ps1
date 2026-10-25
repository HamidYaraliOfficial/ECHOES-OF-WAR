<#
.SYNOPSIS
    ECHOES OF WAR - Windows development environment checker/bootstrapper.
.DESCRIPTION
    Verifies Unreal Engine 5, Visual Studio 2022 (with the "Game development
    with C++" workload), Windows 10/11 SDK and Git are present, then reports
    the .uproject association. Run this once before opening the project.
#>

Write-Host "=== ECHOES OF WAR - Environment Setup Check ===" -ForegroundColor Cyan

function Test-CommandExists {
    param([string]$Name)
    return $null -ne (Get-Command $Name -ErrorAction SilentlyContinue)
}

# 1. Git
if (Test-CommandExists "git") {
    Write-Host "[OK] Git found: $(git --version)" -ForegroundColor Green
} else {
    Write-Host "[MISSING] Git not found. Install from https://git-scm.com/download/win" -ForegroundColor Red
}

# 2. Visual Studio 2022 (via vswhere, shipped with VS installer)
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vswhere) {
    $vsInstall = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Workload.NativeGame -property installationPath
    if ($vsInstall) {
        Write-Host "[OK] Visual Studio 2022 with C++ game development workload found at: $vsInstall" -ForegroundColor Green
    } else {
        Write-Host "[MISSING] Visual Studio found, but the 'Game development with C++' workload is not installed." -ForegroundColor Yellow
        Write-Host "          Open Visual Studio Installer -> Modify -> check 'Game development with C++'." -ForegroundColor Yellow
    }
} else {
    Write-Host "[MISSING] Visual Studio 2022 not detected. Install from https://visualstudio.microsoft.com/vs/" -ForegroundColor Red
}

# 3. Unreal Engine 5 registry check (typical Epic Games Launcher install)
$uePaths = @(
    "C:\Program Files\Epic Games\UE_5.4",
    "C:\Program Files\Epic Games\UE_5.3",
    "C:\Program Files\Epic Games\UE_5.5"
)
$foundUE = $uePaths | Where-Object { Test-Path $_ }
if ($foundUE) {
    Write-Host "[OK] Unreal Engine 5 found at: $($foundUE -join ', ')" -ForegroundColor Green
} else {
    Write-Host "[MISSING] Unreal Engine 5 not found in the default Epic Games install path." -ForegroundColor Red
    Write-Host "          Install UE 5.4+ via the Epic Games Launcher, or update the paths in this script." -ForegroundColor Yellow
}

# 4. Windows SDK
$sdkRegPath = "HKLM:\SOFTWARE\Microsoft\Windows Kits\Installed Roots"
if (Test-Path $sdkRegPath) {
    Write-Host "[OK] Windows SDK installation detected." -ForegroundColor Green
} else {
    Write-Host "[MISSING] Windows 10/11 SDK not detected. Install it via the Visual Studio Installer." -ForegroundColor Red
}

Write-Host ""
Write-Host "=== Project Association ===" -ForegroundColor Cyan
$uproject = Join-Path $PSScriptRoot "..\EchoesOfWar.uproject"
if (Test-Path $uproject) {
    Write-Host "[OK] Found EchoesOfWar.uproject at $uproject" -ForegroundColor Green
    Write-Host "     Right-click it and choose 'Generate Visual Studio project files' before first open." -ForegroundColor Yellow
} else {
    Write-Host "[ERROR] EchoesOfWar.uproject not found next to this script's parent folder." -ForegroundColor Red
}

Write-Host ""
Write-Host "Setup check complete. See Docs/BUILD_GUIDE.md and INSTALLATION.md for full steps." -ForegroundColor Cyan

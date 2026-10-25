<#
.SYNOPSIS
    Builds and packages ECHOES OF WAR in Shipping configuration for Win64
    using UnrealAutomationTool (RunUAT).
#>
param(
    [string]$EnginePath = "C:\Program Files\Epic Games\UE_5.4",
    [string]$ProjectPath = (Resolve-Path (Join-Path $PSScriptRoot "..\EchoesOfWar.uproject")),
    [string]$OutputDir = (Join-Path $PSScriptRoot "..\Build\Shipping")
)

$runUAT = Join-Path $EnginePath "Engine\Build\BatchFiles\RunUAT.bat"
if (-not (Test-Path $runUAT)) {
    Write-Host "[ERROR] Could not find RunUAT.bat under $EnginePath. Pass -EnginePath to this script." -ForegroundColor Red
    exit 1
}

Write-Host "Packaging EchoesOfWar (Shipping, Win64) to $OutputDir ..." -ForegroundColor Cyan
& $runUAT BuildCookRun `
    -project="$ProjectPath" `
    -noP4 -platform=Win64 -clientconfig=Shipping -serverconfig=Shipping `
    -cook -allmaps -build -stage -pak -archive `
    -archivedirectory="$OutputDir"

if ($LASTEXITCODE -ne 0) {
    Write-Host "[FAILED] Packaging exited with code $LASTEXITCODE" -ForegroundColor Red
    exit $LASTEXITCODE
}
Write-Host "[OK] Shipping package complete at $OutputDir" -ForegroundColor Green

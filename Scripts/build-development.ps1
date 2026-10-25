<#
.SYNOPSIS
    Builds ECHOES OF WAR in Development configuration for Win64.
#>
param(
    [string]$EnginePath = "C:\Program Files\Epic Games\UE_5.4",
    [string]$ProjectPath = (Resolve-Path (Join-Path $PSScriptRoot "..\EchoesOfWar.uproject"))
)

$buildBat = Join-Path $EnginePath "Engine\Build\BatchFiles\Build.bat"
if (-not (Test-Path $buildBat)) {
    Write-Host "[ERROR] Could not find Build.bat under $EnginePath. Pass -EnginePath to this script." -ForegroundColor Red
    exit 1
}

Write-Host "Building EchoesOfWarEditor (Development, Win64)..." -ForegroundColor Cyan
& $buildBat EchoesOfWarEditor Win64 Development -project="$ProjectPath" -waitmutex

if ($LASTEXITCODE -ne 0) {
    Write-Host "[FAILED] Build exited with code $LASTEXITCODE" -ForegroundColor Red
    exit $LASTEXITCODE
}
Write-Host "[OK] Development build complete." -ForegroundColor Green

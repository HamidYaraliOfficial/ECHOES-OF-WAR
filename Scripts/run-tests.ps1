<#
.SYNOPSIS
    Runs the EchoesOfWar automation test suite headlessly.
#>
param(
    [string]$EnginePath = "C:\Program Files\Epic Games\UE_5.4",
    [string]$ProjectPath = (Resolve-Path (Join-Path $PSScriptRoot "..\EchoesOfWar.uproject")),
    [string]$TestFilter = "EchoesOfWar"
)

$editorCmd = Join-Path $EnginePath "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
if (-not (Test-Path $editorCmd)) {
    Write-Host "[ERROR] Could not find UnrealEditor-Cmd.exe under $EnginePath." -ForegroundColor Red
    exit 1
}

Write-Host "Running automation tests matching '$TestFilter' ..." -ForegroundColor Cyan
& $editorCmd "$ProjectPath" -ExecCmds="Automation RunTests $TestFilter; Quit" -unattended -nopause -nosplash -log

Write-Host "[OK] Test run complete. See Saved/Logs for the full report." -ForegroundColor Green

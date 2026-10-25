<#
.SYNOPSIS
    Convenience wrapper: runs tests, then a Development build, then a
    Shipping package, stopping at the first failure. Intended for local use
    and as the basis of a CI pipeline step.
#>
param(
    [string]$EnginePath = "C:\Program Files\Epic Games\UE_5.4"
)

$scriptsDir = $PSScriptRoot

Write-Host "== Step 1/3: Automation tests ==" -ForegroundColor Cyan
& (Join-Path $scriptsDir "run-tests.ps1") -EnginePath $EnginePath
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "== Step 2/3: Development build ==" -ForegroundColor Cyan
& (Join-Path $scriptsDir "build-development.ps1") -EnginePath $EnginePath
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "== Step 3/3: Shipping package ==" -ForegroundColor Cyan
& (Join-Path $scriptsDir "build-shipping.ps1") -EnginePath $EnginePath
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "All steps completed successfully." -ForegroundColor Green

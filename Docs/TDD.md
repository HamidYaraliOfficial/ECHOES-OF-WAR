# ECHOES OF WAR — Technical Design Document

## Engine & Language
- Unreal Engine 5 (5.4+), C++ for all simulation-heavy systems.
- Blueprint reserved for designer workflow, UI composition (UMG) and
  wiring gameplay components together — never core simulation logic.

## Module Boundaries
Each `Source/<Module>` folder is its own UBT module with an explicit
`.Build.cs` dependency list (see `Docs/ARCHITECTURE.md` for the full
dependency graph). `EchoesOfWarCore` is dependency-free from gameplay
modules by design, so shared IDs/enums/structs can be included anywhere.

## Simulation Cadence
`UEchoesOfWarGameInstance` owns a real-time timer that accumulates elapsed
seconds and calls `UWorldSimulationSubsystem::AdvanceOneSimDay()` once a
configurable `RealSecondsPerSimDay` threshold is crossed. This keeps the
heavy simulation pass off the render thread's per-frame budget entirely —
see `Source/EchoesOfWar/EchoesOfWarGameInstance.h`.

## Data-Driven Content
Factions, doctrines, unit templates, technology and scenarios are defined
as JSON under `Content/Data/` (see `Docs/SCENARIO_AUTHORING_GUIDE.md`) and
as `UMapDataAsset` for map geometry/topology. The `Tools` module's
`UContentValidationTool` and `UAutomatedScenarioTestRunner` validate this
content without requiring a full editor GUI session, so CI can catch
broken content before merge.

## Persistence
`Save` module: `UCampaignSaveData` stores one JSON blob per subsystem
(keeps modules decoupled), a save-format version, and an MD5 checksum
computed over the full contents (`USaveGameSystem::ComputeChecksum`).
Loading always re-validates the checksum and refuses silently-migrated
saves with no known version path.

## Multiplayer-Ready, Not Multiplayer-Required
The `Networking` module wraps the simulation in a server-authoritative
shell (`AMultiplayerGameState`, `FCommandRequest` /
`IServerAuthoritativeCommand`) without either sitting inside the
simulation modules — `Simulation`, `AI`, `Units`, `Combat`, `Logistics`,
`Economy`, `Politics`, `Research` have zero networking dependencies, so
the single-player build never pays for replication overhead it isn't
using.

## Performance Strategy
World Partition + Level Streaming + HLOD/LOD for the large persistent map;
`UPerformanceProfiler` aggregates per-frame render/sim/AI/network cost so
regressions are visible immediately; distant units run at a coarser
"Simulation Level of Detail" (aggregated strength rather than per-unit
ticks) — the strategic outcome is preserved even though per-unit fidelity
drops for units far from the player's current view.

## Testing
`Tests` module uses Unreal's built-in Automation Test framework
(`IMPLEMENT_SIMPLE_AUTOMATION_TEST`). `Scripts/run-tests.ps1` runs the
suite headlessly via `UnrealEditor-Cmd.exe -ExecCmds="Automation RunTests"`
for CI.

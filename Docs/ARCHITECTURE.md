# ECHOES OF WAR — Architecture Guide

## Module Dependency Graph
```
EchoesOfWarCore            (no gameplay deps)
   ^
   |-- Simulation           (World state: regions, weather, day/night,
   |                         frontline, infrastructure damage, events,
   |                         civilian population)
   |-- Units                (Persistent unit/commander/equipment state,
   |                         orders, comms, morale, fatigue, medical, POW)
   |-- World                (Static map/settlement/terrain data assets)
   |
   |-- Combat  --------------- depends on Units, Simulation
   |-- Logistics ------------- depends on Simulation
   |-- Economy  -------------- depends on Simulation
   |-- Politics -------------- (Diplomacy)
   |-- Research -------------- (Tech tree)
   |-- AI       --------------- depends on Simulation, Units, Logistics,
   |                            Economy
   |-- Save     --------------- depends on nothing gameplay-specific
   |                            (stores per-subsystem JSON blobs)
   |-- Networking ------------- depends on nothing gameplay-specific
   |                            (server-authoritative command shell)
   |-- UI       --------------- depends on EchoesOfWarCore only
   |                            (theme/localization/advisors/news/
   |                             chronicle/achievements/replay/AAR)
   |-- Tools (Editor) --------- depends on World, Simulation
   |-- EchoesOfWar (game) ----- depends on all of the above
   |-- Tests (DeveloperTool) -- depends on the modules under test
```

## Why This Shape
- **EchoesOfWarCore has no gameplay dependents.** Every ID type
  (`FRegionId`, `FFactionId`, `FUnitId`, ...) and shared enum lives here so
  any two gameplay modules can refer to the same entities without
  depending on each other directly.
- **Simulation is the single source of truth for world state.**
  `UWorldSimulationSubsystem` owns `FRegionState` for every region; AI,
  Logistics, Economy and UI all read from it rather than keeping their own
  copies, so there is never a "which value is current" ambiguity.
- **AI depends on Simulation/Units/Logistics/Economy but not vice versa.**
  The strategic AI (`UFactionAICommander`) and tactical AI
  (`ATacticalAIController`) only ever read what those modules expose
  (including intelligence estimates with confidence levels), matching the
  "AI must not cheat" requirement.
- **Save and Networking are decoupled from the simulation modules.** Save
  stores opaque JSON blobs per subsystem; Networking wraps command
  submission without embedding itself in simulation logic. This means the
  simulation core can be unit-tested with zero Save/Networking
  dependencies, and a non-multiplayer build carries no replication cost.

## Threading Model
- **Render thread:** UMG/Slate widgets, camera, input.
- **Simulation clock (GameInstance timer):** `AdvanceOneSimDay()` and its
  sub-tick functions (`TickRegionEconomy`, `TickRegionPopulation`,
  `TickRegionStability`, `RecomputeFrontlineFlags`) run on this cadence,
  not on render tick.
- **Background workers:** long content-validation or automated-scenario
  test runs (`Tools` module) are designed to run headlessly outside the
  interactive editor/game process entirely (see `Scripts/run-tests.ps1`).

## Data Flow Example: A Region Gets Bombed
1. Combat resolves an engagement (`UCombatResolutionSystem`).
2. The attacking side calls
   `UWorldSimulationSubsystem::ApplyWarDamage(Region, Amount, Infrastructure::Road)`.
3. `FRegionState::InfrastructureIntegrity[Road]` drops, `AccumulatedWarDamage`
   rises, `CivilianMorale`/`Security` take an immediate hit.
4. Next sim-day, `TickRegionEconomy` reads the now-lower
   `GetInfrastructureAverage()` and reduces `EffectiveOutput`; `Logistics`
   routes touching that region see reduced `RoadIntegrity` and therefore
   lower `GetEffectiveThroughput()`.
5. `UDynamicEventEngine` may now find a "supply crisis" event's conditions
   satisfied for that region and surface it; `UWarNewsSystem` and
   `UWarChronicle` both record it from the same `FWarLogEntry`.
6. `UFactionAICommander` for whichever faction owns/threatens the region
   re-evaluates on its next strategic cycle, using the same up-to-date
   region data — never a stale or hidden copy.

## Extending the Codebase
Add a new module under `Source/`, give it a `.Build.cs`, register it in
`EchoesOfWar.uproject` and both `Target.cs` files, and depend only on
`EchoesOfWarCore` plus whichever modules you actually need — keeping the
graph above acyclic is what keeps compile times and testability sane as
the project grows.

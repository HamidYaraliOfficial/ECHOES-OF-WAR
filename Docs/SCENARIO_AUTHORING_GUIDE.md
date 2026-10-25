# ECHOES OF WAR — Scenario Authoring Guide

## Two Kinds of Data
1. **Map geometry & topology** — a `UMapDataAsset` (Editor Utility Widget:
   `UScenarioEditorUtility`) holding `FSettlementData`,
   `FInfrastructureLink`, `FResourceNodeData` and `FTerrainFeature` entries.
2. **Rules & starting conditions** — a scenario JSON file (see
   `Content/Data/Scenarios/scenario_001.json`) pointing at a map asset and
   listing playable/AI factions, victory conditions and the starting sim
   day.

## Building a Map in the Scenario Editor
1. Open the Scenario Editor Utility Widget from the Editor Utility panel.
2. `CreateNewSettlement(Map, RegionId, Type, Position)` for every city,
   village, base, industrial zone, port or airport.
3. `CreateInfrastructureLink(Map, From, To, LinkType)` for every road,
   bridge or railway connecting them.
4. Add `FResourceNodeData` entries for iron/fuel/electronics/food deposits.
5. Run `UContentValidationTool::ValidateMap` — fix every fatal issue
   (missing reference, duplicate id, zero settlements) before proceeding.

## Writing Victory Conditions
`scenario_001.json`'s `victoryConditions` array is intentionally simple and
extensible — `ControlRegionCount` and `SurviveDays` are the two shipped
types; add new types by extending the scenario-loading code path and
keeping the same "type + parameters" JSON shape so existing scenarios stay
valid.

## Multi-Stage Operations & Triggers
Operational-level missions are defined as an ordered list of stages, each
with a trigger condition drawn from the same condition vocabulary as
`FEventCondition` (region security below X, enemy supply below Y, weather
state, reinforcement arrived, etc.) — reusing that vocabulary means
anything the Dynamic Event Engine can check, a mission trigger can check
too.

## Testing a Scenario Headlessly
`UAutomatedScenarioTestRunner::RunHeadless(ScenarioId, SimDaysToRun)` is
designed to load your scenario into a headless `UGameInstance` and advance
the simulation without any rendering, asserting basic invariants (no
faction's economy locks permanently negative, the AI keeps producing
decisions every cycle). Wire this into `Scripts/run-tests.ps1` for CI.

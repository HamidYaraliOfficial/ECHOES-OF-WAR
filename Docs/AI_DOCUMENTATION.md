# ECHOES OF WAR — AI Documentation

## Three Layers
1. **Squad/Unit (`ATacticalAIController::EvaluateTacticalDecision`)** —
   reacts to `FTacticalPerception` (only what that unit can see: visible
   enemy strength, own strength/morale/supply, local terrain, suppression).
2. **Commander (`UFactionAICommander`)** — strategic cycle over all owned
   regions: reinforcement priority, attack opportunities, ceasefire
   requests, each backed by a `FAIDecision.ReasoningTrace` you can print
   with `UAIDebugger`.
3. **Army/Doctrine (`FDoctrineProfile`, `UDoctrineSystem`)** — biases every
   decision at both layers above (defensive vs. mobile vs. fire-support vs.
   logistics-heavy, plus risk tolerance).

## No-Cheating Guarantee
`UFactionAICommander::KnownEnemyStrengthEstimate` is populated exclusively
from `UIntelligenceSystem::GetBestEstimate`, which only aggregates
`FIntelReport`s actually submitted by Recon/Drone/Radar/etc. sources with
their own confidence levels. There is no code path that lets the AI read
`FRegionState` for a region it has not observed under `UFogOfWarSystem`.

## Debugging AI Decisions
```cpp
TArray<FAIDecision> Decisions = Commander->EvaluateStrategicCycle(WorldSim);
FString Report = AIDebugger->FormatCycleReport(Decisions);
UE_LOG(LogTemp, Log, TEXT("%s"), *Report);
```
Each decision's `ReasoningTrace` lines are plain, human-readable strings
built directly from the same numbers used to compute `Priority` — nothing
is summarized or hidden between the calculation and the log.

## Adding a New Decision Type
1. Add a private `Evaluate...` method to `UFactionAICommander` that reads
   only from data the faction could plausibly know (world sim + intel +
   doctrine).
2. Populate `ReasoningTrace` with the concrete numbers behind the score.
3. Call it from `EvaluateStrategicCycle` and let the existing
   priority-sort handle ordering — do not special-case ordering elsewhere.

## Testing AI
`Tests/AITests.cpp` currently unit-tests the documented decision rules
directly; `UAutomatedScenarioTestRunner` (Tools module) is the intended
home for full integration runs that drive a real `UWorldSimulationSubsystem`
through many simulated days and assert the AI never stalls or produces
NaN/garbage priorities.

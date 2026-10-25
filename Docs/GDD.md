# ECHOES OF WAR — Game Design Document

## Vision
ECHOES OF WAR is a dynamic tactical strategy, war-simulation and real-time
command game. The player commands a military force across a persistent,
simulation-driven world rather than a fixed sequence of missions. Every
number the player sees — population, morale, supply, infrastructure,
industrial output — is produced by a running simulation and can move in
response to the player's decisions and the AI's.

## Pillars
1. **Command, not micromanagement.** The player operates at Strategic,
   Operational and Tactical layers; the simulation resolves the detail.
2. **A living world.** Frontlines emerge from force disposition, supply and
   morale — they are never scripted lines.
3. **Consequential decisions.** Losing a factory, a commander or a supply
   route has a real, lasting effect on what the player can do next.
4. **Honest AI.** Faction AI reads the same simulation data the Fog of War
   exposes to the player — it does not cheat with hidden omniscience.

## Core Loop
Observe (Strategic/Tactical Map, Intelligence) → Decide (Orders, Operation
Planner, Research, Production) → Advance simulation (one sim-day at a time,
on a player-configurable clock) → Review (Event Feed, War News, After Action
Review) → repeat.

## Layers of Play
- **Strategic:** military policy, budget, research priorities, front
  priority, diplomacy.
- **Operational:** brigade/battalion/task-force movement, supply routing,
  reconnaissance missions, multi-phase operations with triggers.
- **Tactical:** direct command of units in an active engagement.

## Systems Summary
See `Docs/ARCHITECTURE.md` for the technical breakdown. Gameplay-facing
systems include: World Simulation, Frontline Simulation, Fog of
War/Intelligence, Command Hierarchy & Orders, Logistics & Supply Chain,
Research, Military Industry & Economy, Diplomacy, Dynamic Events,
Persistent Units (experience/fatigue/morale/equipment), Medical & Prisoner
handling, War Cabinet & Advisors, Battle Replay & After Action Review, War
News & Chronicle, Achievements, Scenario Editor and Modding.

## Content Scope & Honest Status
This repository is a **large, working C++/Unreal Engine 5 architectural
foundation** implementing the systems above with real (not mocked) logic —
simulation math, AI decision rules, supply-chain flow, save/checksum
validation, and more — organized into clean, modular, testable code. It is
**not** a finished, art-complete, balanced, shipped title: building that
from here still requires UE5 assets (maps, meshes, VFX, audio), extensive
balancing, QA and additional content authored through the Scenario Editor.
Every system here is designed to be extended rather than replaced.

## Combat Design Note
Combat resolution is intentionally abstracted to strategic values (combat
effectiveness, terrain, weather, numbers) rather than real-world weapons
data, keeping the focus on command and simulation rather than a ballistics
model.

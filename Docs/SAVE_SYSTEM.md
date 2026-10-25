# ECHOES OF WAR — Save System Documentation

## Format
`UCampaignSaveData` (Save module) is the root object:
- `SaveFormatVersion` — integer, bumped whenever the on-disk shape changes.
- `ScenarioId`, `CurrentSimDay` — top-level campaign identity.
- `SubsystemBlobsJson: TMap<FString, FString>` — one JSON blob per
  subsystem (`"WorldSim"`, `"Units"`, `"Economy"`, ...), so each module
  can evolve its own serialization independently.
- `IntegrityChecksum` — MD5 over the version, scenario id, sim day and the
  sorted subsystem blobs (`USaveGameSystem::ComputeChecksum`).

## Slots, Auto-Save, Checkpoints
`FSaveSlotInfo` describes each slot (`SlotName`, `Timestamp`,
`bIsAutoSave`, `bIsCorrupt`). The intended policy: auto-save on sim-day
boundaries and after major operations complete; manual saves on demand;
checkpoints before a played-out tactical engagement so a bad fight can be
retried without losing the whole campaign session.

## Corruption Handling
`USaveGameSystem::ValidateIntegrity` recomputes the checksum and compares
it against the stored one. A mismatch marks the slot `bIsCorrupt = true`
in its `FSaveSlotInfo` rather than silently loading bad data — the UI is
expected to warn the player and offer the next-most-recent slot/auto-save.

## Version Migration
`USaveGameSystem::MigrateToCurrentVersion` walks version-by-version
(`switch (SaveData->SaveFormatVersion)`), applying one explicit,
auditable transformation per step. If no case exists for the save's
current version, migration fails closed (returns `false`) rather than
guessing — never silently drop or reinterpret unknown fields.

## Adding a New Save Field
1. Add the field inside the owning subsystem's own serialization code
   (not to `UCampaignSaveData` directly) and re-encode that subsystem's
   JSON blob.
2. Bump `USaveGameSystem::CurrentSaveFormatVersion`.
3. Add a `case` to `MigrateToCurrentVersion` that fills a sensible default
   for saves that predate the field.
4. Add/extend a `Tests/SaveLoadTests.cpp` case covering the new field.

#pragma once
#include "Modules/ModuleManager.h"

/**
 * EchoesOfWarCore
 * Foundation module: shared IDs, enums, structs and utility types used by
 * every other gameplay module (Simulation, AI, Units, Combat, Logistics,
 * Economy, Politics, Research, World, Save, Networking, UI).
 * Kept dependency-free from gameplay modules so it can be included anywhere
 * without circular references.
 */
class FEchoesOfWarCoreModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

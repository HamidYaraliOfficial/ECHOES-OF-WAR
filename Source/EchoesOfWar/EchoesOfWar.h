#pragma once
#include "Modules/ModuleManager.h"

class FEchoesOfWarModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

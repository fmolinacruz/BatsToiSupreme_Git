#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBatsToiSupreme_RealEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

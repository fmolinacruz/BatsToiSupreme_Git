#include "BatsToiSupreme_RealEditor.h"

#include "UI/Styling/BTEditorStyle.h"

#define LOCTEXT_NAMESPACE "FBatsToiSupreme_RealEditorModule"

void FBatsToiSupreme_RealEditorModule::StartupModule()
{
	InitializeStyles();
}

void FBatsToiSupreme_RealEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	ShutdownStyles();
}

void FBatsToiSupreme_RealEditorModule::RegisterMenus()
{
}

void FBatsToiSupreme_RealEditorModule::RegisterComboMenus()
{
}

void FBatsToiSupreme_RealEditorModule::InitializeStyles()
{
	FBTEditorStyle::Initialize();
	FBTEditorStyle::ReloadTextures();
}

void FBatsToiSupreme_RealEditorModule::ShutdownStyles()
{
	FBTEditorStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBatsToiSupreme_RealEditorModule, BatsToiSupreme_RealEditor)

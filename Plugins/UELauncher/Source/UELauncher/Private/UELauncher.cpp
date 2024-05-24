// Copyright Epic Games, Inc. All Rights Reserved.

#include "UELauncher.h"

#include "IStructureDetailsView.h"

#define LOCTEXT_NAMESPACE "FUELauncherModule"

void FUELauncherModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		TEXT("PropertyEditor"));
	PropertyEditorModule.RegisterCustomPropertyTypeLayout(
		TEXT("PropertyMatchMapping"),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FCustomPropertyMatchMappingDetails::MakeInstance));
}

void FUELauncherModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUELauncherModule, UELauncher)

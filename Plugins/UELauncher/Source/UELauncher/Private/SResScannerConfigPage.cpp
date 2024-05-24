// Fill out your copyright notice in the Description page of Project Settings.


#include "SResScannerConfigPage.h"
#include "EditorStyleSet.h"
#include "IStructureDetailsView.h"
#include "ScannerSettingsDetails.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SResScannerConfigPage::Construct(const FArguments& InArgs)
{
	ScannerConfig = MakeShareable(new FScannerConfig);
	CreateScannerStructureDetailView();


	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .HAlign(HAlign_Right)
		  .Padding(4, 4, 10, 4)
		// [
		//
		// ]
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .Padding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			[
				SettingsView->GetWidget()->AsShared()

			]
		]
	];
}

void SResScannerConfigPage::CreateScannerStructureDetailView()
{
	// 创建一个属性面板
	FPropertyEditorModule& EditorModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowSearch = true;
		DetailsViewArgs.bHideSelectionTip = true;
		DetailsViewArgs.bLockable = false;
		DetailsViewArgs.bSearchInitialKeyFocus = true;
		DetailsViewArgs.bUpdatesFromSelection = false;
		DetailsViewArgs.NotifyHook = nullptr;
		DetailsViewArgs.bShowOptions = true;
		DetailsViewArgs.bShowModifiedPropertiesOption = false;
		DetailsViewArgs.bShowScrollBar = false;
	}

	FStructureDetailsViewArgs StructureViewArgs;
	{
		StructureViewArgs.bShowObjects = true;
		StructureViewArgs.bShowAssets = true;
		StructureViewArgs.bShowClasses = true;
		StructureViewArgs.bShowInterfaces = true;
	}


	// 创建细节面板
	SettingsView = EditorModule.CreateStructureDetailView(DetailsViewArgs, StructureViewArgs, nullptr);
	FStructOnScope* Struct = new FStructOnScope(FScannerConfig::StaticStruct(),
	                                            reinterpret_cast<uint8*>(ScannerConfig.Get()));
	SettingsView->GetDetailsView()->RegisterInstancedCustomPropertyLayout(
		FScannerConfig::StaticStruct(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FScannerSettingsDetails::MakeInstance));
	SettingsView->SetStructureData(MakeShareable(Struct));
}

// SettingsView->SetStructureData(MakeShareable(Struct));


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

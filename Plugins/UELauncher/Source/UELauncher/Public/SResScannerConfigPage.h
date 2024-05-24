// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FScannerConfig.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class UELAUNCHER_API SResScannerConfigPage : public SCompoundWidget
{
public:
	TSharedPtr<FScannerConfig> ScannerConfig;
	TSharedPtr<IStructureDetailsView> SettingsView;
	
public:
	SLATE_BEGIN_ARGS(SResScannerConfigPage)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

public:
	void CreateScannerStructureDetailView();
};

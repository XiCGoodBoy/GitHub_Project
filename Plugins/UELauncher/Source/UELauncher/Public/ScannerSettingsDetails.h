// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"


class FScannerSettingsDetails : public IDetailCustomization
{
public:
	// 重载IDetailCustomization接口函数
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FScannerSettingsDetails());
	}

	
};

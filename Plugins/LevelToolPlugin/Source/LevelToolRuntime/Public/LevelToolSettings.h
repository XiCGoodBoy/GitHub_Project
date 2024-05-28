// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "../UI/LevelLoadBaseWidget.h"
#include "../Component/LevelToolComponent.h"
#include "../Type/DataAssetType.h"
#include "LevelToolSettings.generated.h"

/**
 * 该文件用于配置关卡工具插件需要的参数
 */
UCLASS(config="LevelToolSetting", defaultconfig,BlueprintType,Blueprintable)
class LEVELTOOLRUNTIME_API ULevelToolSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	virtual FName GetContainerName() const override
	{
		return FName(TEXT("Project"));
	}
	virtual FName GetCategoryName() const override
	{
		return FName(TEXT("ToolPlugin"));
	}
	virtual FName GetSectionName() const override
	{
		return FName(TEXT("LevelToolSettings"));
	}

public:
	/* 用于确定一开始是否启用关卡加载,在ULevelToolSubsystem中实现 */
	UPROPERTY(Config,EditAnywhere,BlueprintReadWrite,Category="LevelToolSetting")
	bool bEnable_Start_Level_Load=true;

	/* 用于在关卡加载时,创建显示加载进度的UI */
	UPROPERTY(Config,EditAnywhere,BlueprintReadWrite,Category="LevelToolSetting",meta=(EditCondition="bEnable_Start_Level_Load"))
	TSubclassOf<ULevelLoadBaseWidget>Level_Load_UI_Class=LoadClass<ULevelLoadBaseWidget>(this,TEXT("/LevelToolPlugin/Example/Example_Load_Level_WBP.Example_Load_Level_WBP_C"));
	
	/* 用于设置关卡加载UI的层级 */
	UPROPERTY(Config,EditAnywhere,BlueprintReadWrite,Category="LevelToolSetting",meta=(EditCondition="bEnable_Start_Level_Load"))
	int32 Level_Load_Z_Order=99;
	
	/* 用于进行关卡加载时读取的配置表 */
	UPROPERTY(Config,EditAnywhere,BlueprintReadWrite,Category="LevelToolSetting",meta=(EditCondition="bEnable_Start_Level_Load"))
	TSoftObjectPtr<ULevelArrayData>Level_Load_Config_Data=LoadObject<ULevelArrayData>(this,TEXT("/LevelToolPlugin/Data/DefaultLevelData.DefaultLevelData"));
	
	/* 获取ULevelToolSettings对象 */
	UFUNCTION(BlueprintPure,Category="LevelToolPlugin|LevelCommonLib")
	static inline ULevelToolSettings* GetLevelToolCommonSetting()
	{
		static ULevelToolSettings* LevelToolSettings;
		if (!LevelToolSettings)
		{
			LevelToolSettings=GetMutableDefault<ULevelToolSettings>();
			UE_LOG(LogTemp,Warning,TEXT("获取默认ULevelToolSettings对象"));
		}
		return LevelToolSettings;
	}
};








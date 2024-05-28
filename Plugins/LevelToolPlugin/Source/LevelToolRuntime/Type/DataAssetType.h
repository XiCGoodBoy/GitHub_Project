// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HelperStructType.h"
#include "LevelToolCommon/FunctionLibrary/LevelToolCommonLibrary.h"

#include "DataAssetType.generated.h"


/* 数组关卡数据 */
UCLASS(Blueprintable,BlueprintType)
class LEVELTOOLRUNTIME_API ULevelArrayData : public UDataAsset
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	/* 读取当前的蓝图加载关卡 */
	UFUNCTION(CallInEditor,Category="ULevelArrayData")
	void ReadCurrentLevel()
	{
		//先清理
		VisibleLevels.Empty();
		NoVisibleLevels.Empty();
		
		TArray<ULevelStreaming*>StreamingLevels=ULevelToolCommonLibrary::GetWorldAllStreamingLevel(ULevelToolCommonLibrary::GetEditorWorld());
		for(const ULevelStreaming* TemLevelStreaming:StreamingLevels)
		{
			//不为始终加载
			if (!TemLevelStreaming->ShouldBeAlwaysLoaded())
			{
				if (TemLevelStreaming->GetShouldBeVisibleInEditor())
				{
					VisibleLevels.AddUnique(ULevelToolCommonLibrary::GetUWorldPtr(TemLevelStreaming));
				}
				else
				{
					NoVisibleLevels.AddUnique(ULevelToolCommonLibrary::GetUWorldPtr(TemLevelStreaming));
				}
				
			}
		}
		UE_LOG(LogTemp,Warning,TEXT("读取当前可视的蓝图加载关卡到VisibleLevels数组中"));
		UE_LOG(LogTemp,Warning,TEXT("读取当前不可视的蓝图加载关卡到NoVisibleLevels数组中"));

		//通知该数据资源已被修改
		Modify();
	}
	
	/* 读取当前可视的蓝图加载关卡到VisibleLevels数组中 */
	UFUNCTION(CallInEditor,Category="ULevelArrayData")
	void ReadCurrentVisibleLevelForVisibleLevels()
	{
		//先清理
		VisibleLevels.Empty();
		
		TArray<ULevelStreaming*>StreamingLevels=ULevelToolCommonLibrary::GetWorldAllStreamingLevel(ULevelToolCommonLibrary::GetEditorWorld());
		for(const ULevelStreaming* TemLevelStreaming:StreamingLevels)
		{
			//不为始终加载
			if (!TemLevelStreaming->ShouldBeAlwaysLoaded())
			{
				if (TemLevelStreaming->GetShouldBeVisibleInEditor())
				{
					VisibleLevels.AddUnique(ULevelToolCommonLibrary::GetUWorldPtr(TemLevelStreaming));
				}
			}
		}
		
		UE_LOG(LogTemp,Warning,TEXT("读取当前可视的蓝图加载关卡到VisibleLevels数组中"));

		//通知该数据资源已被修改
		Modify();
	}

	/* 读取当前不可视的蓝图加载关卡到NoVisibleLevels数组中 */
	UFUNCTION(CallInEditor,Category="ULevelArrayData")
	void ReadCurrentNoVisibleLevelForNoVisibleLevels()
	{
		//先清理
		NoVisibleLevels.Empty();
		
		TArray<ULevelStreaming*>StreamingLevels=ULevelToolCommonLibrary::GetWorldAllStreamingLevel(ULevelToolCommonLibrary::GetEditorWorld());
		for(const ULevelStreaming* TemLevelStreaming:StreamingLevels)
		{
			//不为始终加载
			if (!TemLevelStreaming->ShouldBeAlwaysLoaded())
			{
				if (!TemLevelStreaming->GetShouldBeVisibleInEditor())
				{
					NoVisibleLevels.AddUnique(ULevelToolCommonLibrary::GetUWorldPtr(TemLevelStreaming));
				}
			}
		}
		UE_LOG(LogTemp,Warning,TEXT("读取当前不可视的蓝图加载关卡到NoVisibleLevels数组中"));

		//通知该数据资源已被修改
        Modify();
	}
#endif
	
	
	/* 显示的关卡 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ULevelArrayData")
	TArray<TSoftObjectPtr<UWorld>>VisibleLevels;
	/* 隐藏的关卡 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ULevelArrayData")
	TArray<TSoftObjectPtr<UWorld>>NoVisibleLevels;
};

/* Map关卡数据 */
UCLASS(Blueprintable,BlueprintType)
class LEVELTOOLRUNTIME_API ULevelMapData:public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ULevelMapData")
	TMap<FName,TSoftObjectPtr<UWorld>>VisibleLevelMap;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ULevelMapData")
	TMap<FName,FLevelArrayHelperStruct>NoVisibleLevelArrayMap;

};



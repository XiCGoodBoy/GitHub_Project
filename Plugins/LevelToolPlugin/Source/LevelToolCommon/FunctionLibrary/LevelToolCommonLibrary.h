// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelToolCommonLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LEVELTOOLCOMMON_API ULevelToolCommonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	//获取编辑器世界
	UFUNCTION(BlueprintPure,Category = "ULevelToolCommonLibrary")
	static UWorld* GetEditorWorld();


#pragma region 子关卡状态
	/* 流关卡在编辑中当前是否为可视状态 */
	UFUNCTION(BlueprintPure,Category="ULevelToolCommonLibrary",meta=(WorldContext="WorldContextObject"))
	static bool GetLevelVisualityInEditor(const TSoftObjectPtr<UWorld> Level, const UObject* WorldContextObject);

	/* 检测该关卡是否为始终加载 */
	UFUNCTION(BlueprintPure,Category="ULevelToolCommonLibrary",meta=(WorldContext="WorldContextObject",HidePin="WorldContextObject"))
	static bool IsAlwaysLoad(const TSoftObjectPtr<UWorld> Level, const UObject* WorldContextObject);
#pragma endregion

#endif

#pragma region 流关卡与UWorld之间转换
	//通过软对象指针获取流关卡
	UFUNCTION(BlueprintPure,Category = "ULevelToolCommonLibrary",meta=(WorldContext="WorldContextObject"))
	static ULevelStreaming* GetStreamingLevel(const UObject* WorldContextObject,const TSoftObjectPtr<UWorld>&InWorld);

	//获取指向流关卡资源的World软指针
	UFUNCTION(BlueprintPure,Category="ULevelToolCommonLibrary")
	static TSoftObjectPtr<UWorld> GetUWorldPtr(const ULevelStreaming* StreamingLevel);
#pragma endregion

#pragma region UWorld中关卡的获取
	//获取Persistent关卡
	UFUNCTION(BlueprintPure,Category="ULevelToolCommonLibrary",meta=(WorldContext="WorldContextObject"))
	static ULevel* GetWorldPersistentLevel(UWorld* InWorld);
	
	//获取所有的流关卡
	UFUNCTION(BlueprintPure,Category="ULevelToolCommonLibrary",meta=(WorldContext="WorldContextObject"))
	static TArray<ULevelStreaming*> GetWorldAllStreamingLevel(const UObject* WorldContextObject);

	//获取所有的引用的关卡
	UFUNCTION(BlueprintPure,Category = "ULevelToolCommonLibrary")
	static TArray<ULevel*> GetWorldLevels(const TSoftObjectPtr<UWorld> InWorld);
#pragma endregion

#pragma region 获取关卡信息
	//获取流关卡的资源名
	UFUNCTION(BlueprintPure,Category = "ULevelToolCommonLibrary")
	static FString GetStreamingLevelName(const ULevelStreaming* StreamingLevel);

	//获取ULevel的资源名
	UFUNCTION(BlueprintPure,Category="ULevelToolCommonLibrary",meta=(WorldContext="WorldContextObject"))
	static FString GetLevelName(ULevel* InLevel,const bool bClearPrefix=true);

	//获取UWorld的实际资源名
	UFUNCTION(BlueprintPure,Category = "LevelToolPlugin|LevelCommonLib")
	static FName GetUWorldName(const TSoftObjectPtr<UWorld>&InWorld);

	
#pragma endregion
	
};

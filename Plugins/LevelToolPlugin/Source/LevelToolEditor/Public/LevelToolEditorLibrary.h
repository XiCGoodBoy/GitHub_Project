// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelToolEditorLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LEVELTOOLEDITOR_API ULevelToolEditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#pragma region 关卡引用
public:
	UFUNCTION(BlueprintPure,Category = "LevelEditorLibrary")
	static TArray<ULevel*> GetWorldCollectionLevels(const TSoftObjectPtr<UWorld> InWorld);
	
#pragma endregion	
	
	//获取流关卡在编辑器世界下是否是可见的
	UFUNCTION(BlueprintPure,Category = "LevelToolPlugin|LevelEditorLib")
	static bool GetStreamingLevelIsVisible(const ULevelStreaming* InLevelStreaming);
	
	//缩放场景核心方法
	static void ScaleScene(float ScaleValue=1,bool bScaleChildLevel=false,float ReferenceOriginTime=1.0f);

	//缩放单个场景
	UFUNCTION(BlueprintCallable,Category="LevelToolPlugin|Editor")
	static void ScaleSceneSingleLevel(float ScaleValue=1,float ReferenceOriginTime=1);

	//缩放多个场景
	UFUNCTION(BlueprintCallable,Category="LevelToolPlugin|Editor")
	static void ScaleScenemultipleLevel(float ScaleValue=1,float ReferenceOriginTime=1);
	
	
	/*
	 *获取世界大纲中所有的文件夹
	 *@ActorFolderNames			获取Actor的文件夹
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, Category = "LevelToolPlugin|WorldOutline|Folder",meta=(WorldContext="WorldContextObject"))
	static bool GetWorldOutLineAllFolderByWorld(const UWorld* InWorld, TArray<FName>& ActorFolderNames);

	/*
	 *在世界大纲中创建文件夹
	 *@FolderName				要创建的文件夹
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, Category = "LevelToolPlugin|WorldOutLine|Folder", meta = (WorldContext = "WorldContextObject"))
		static bool CreateFolderInWorldOutline(UWorld* InWorld, const FName FolderName);

	/*
	 *在世界大纲中删除文件夹
	 *@FolderName				要删除的文件夹
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, Category = "LevelToolPlugin|WorldOutLine|Folder", meta = (WorldContext = "WorldContextObject"))
		static bool DeleteFolderInWorldOutline(UWorld* InWorld,FName FolderName);
	
	/*
	 *在世界大纲中移动文件夹到到指定的文件夹下
	 * @ParentFolderName		父文件夹
	 * @ChildFolderName			子文件夹
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ToolPlugin|WorldOutLine|Folder", meta = (WorldContext = "WorldContextObject"))
	static bool MoveFolderToFolder(const FName ParentFolderName,FName ChildFolderName, const UObject* WorldContextObject);

private:
	//过滤其他的Actor
	static void FilterOtherActors(TArray<AActor*>&SourceActors);

	//缩放场景Actor
	static void ScaleLevelActors(ULevel* WillScaleLevel,const float ScaleValue);




#pragma region UTexture相关
public:
	/* 设置UTexture的MipGenSettings为NoMipmaps */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UTexture2D")
	static void SetUTextureMipGenSettings(UTexture* InUTexture);

	/* 设置UTexture的LODGroup为UI */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UTexture2D")
	static void SetUTextureLODGroup(UTexture* InUTexture);
	
	/* 清除UTexture2D的Source File */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UTexture2D")
	static void ClearUTexture2DSourceFile(UTexture* InUTexture);
#pragma endregion








	
};

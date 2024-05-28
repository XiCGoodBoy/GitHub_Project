// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Engine.h"
#include "LevelToolRuntimeLibrary.generated.h"

/* Level State */
UENUM(BlueprintType)
enum class ELevelToolPluginLevelState : uint8
{
	Unknown,
	Removed,
	Unloaded,
	FailedToLoad,
	Loading,
	LoadedNotVisible,
	MakingVisible,
	LoadedVisible,
	MakingInvisible
};

namespace ULevelToolPlugin
{
	static inline ELevelStreamingState CastELevelToolPluginLevelStateToELevelStreamingState(const ELevelToolPluginLevelState LevelState)
	{
		switch (LevelState)
		{
		case ELevelToolPluginLevelState::Removed:
			return ELevelStreamingState::Removed;
		case ELevelToolPluginLevelState::Unloaded:
			return ELevelStreamingState::Unloaded;
		case ELevelToolPluginLevelState::FailedToLoad:
			return ELevelStreamingState::FailedToLoad;
		case ELevelToolPluginLevelState::Loading:
			return ELevelStreamingState::Loading;
		case ELevelToolPluginLevelState::LoadedNotVisible:
			return ELevelStreamingState::LoadedNotVisible;
		case ELevelToolPluginLevelState::MakingVisible:
			return ELevelStreamingState::MakingVisible;
		case ELevelToolPluginLevelState::LoadedVisible:
			return ELevelStreamingState::LoadedVisible;
		case ELevelToolPluginLevelState::MakingInvisible:
			return ELevelStreamingState::MakingInvisible;
		default:
			return ELevelStreamingState::Removed;
		}
	}
}




UENUM(BlueprintType)
namespace ULevelToolCommonLibraryNameSpace
{
	enum EWorldType
	{
		None, 
		Eidtor,
		Game 
	};
}

UCLASS()
class LEVELTOOLRUNTIME_API ULevelToolRuntimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/*
	 * 获取当前所处于的世界状态
	 * @InPlayerController Be used to get world's playercontroller
	 */
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="LevelToolPlugin|RuntimeLibrary|World",meta=(WorldContext="WorldContextObject"))
	static bool GetCurrentWorld(const UObject* WorldContextObject,UWorld*&RuntimeWorld);

#pragma region 关卡变换
public:
	/* 设置流关卡的世界变化位置 */
	UFUNCTION(BlueprintPure,Category="ULevelToolRuntimeLibrary",meta=(WorldContext="WorldContextObject"))
	static FVector GetChildLevelLocation(const UObject* WorldContextObject,TSoftObjectPtr<UWorld>InWorld);
	
	/* 设置流关卡的世界变化位置 */
	UFUNCTION(BlueprintCallable,Category="ULevelToolRuntimeLibrary",meta=(WorldContext="WorldContextObject"))
	static void SetChildLevelLocation(const UObject* WorldContextObject,TSoftObjectPtr<UWorld>InWorld,const FVector Location);

	
#pragma endregion
	
#pragma region 获取关卡Actor
	/* 获取关卡的所有Actor */
	UFUNCTION(BlueprintPure,Category="LevelToolPlugin|StreamingLevel", meta = (WorldContext = WorldContextObject),DisplayName="GetLevelActors")
	static TArray<AActor*> GetLevelActorsBySoftWord(const UObject* WorldContextObject,TSoftObjectPtr<UWorld>InWorld);
#pragma endregion

#pragma region 获取流关卡状态
	/*
	 *获取给定的流关卡对象的状态
	 * @LevelStreaming			要获取状态的流关卡
	 * @CurrentState			获取的流关卡状态
	 * returen					成功获取状态返回true,否则返回false;
	 */
	UFUNCTION(BlueprintPure, Category = "ULevelToolRuntimeLibrary", meta = (WorldContext = WorldContextObject))
	static FString GetStreamingLevelState(const ULevelStreaming* LevelStreaming);

	/* 返回流关卡是否处于某个状态 */
	UFUNCTION(BlueprintPure,DisplayName="LevelStateEqual", Category = "ULevelToolRuntimeLibrary", meta = (WorldContext = WorldContextObject))
	static bool SingleLevelStateEqual(const ULevelStreaming* Level,const ELevelToolPluginLevelState LevelState);

	/* 返回流关卡是否处于某个状态 */
    UFUNCTION(BlueprintPure,DisplayName="LevelStateEqual",Category = "ULevelToolRuntimeLibrary", meta = (WorldContext = WorldContextObject))
    static bool MultileLevelStateEqual(const TArray<ULevelStreaming*>Levels,const ELevelToolPluginLevelState LevelState);
	
#pragma endregion
	
	/*
	*获取流关卡的ULevel
		 *@LevelStreaming 需要获取ULevel的流关卡对象
		 * return		  返回ULevel对象的指针
		 */
	UFUNCTION(BlueprintCallable,Category="LevelToolPlugin|StreamingLevel", meta = (WorldContext = WorldContextObject))
	static  ULevel* GetULevelByStreamingObject(const UObject* WorldContextObject,ULevelStreaming* LevelStreaming);
	
	/*
	 *获取关卡中的Actor
	 * @WorldContextObject：				世界上下文对象
	 * @Level:								要查找的关卡目标
	 * @LevelActorTarray：					查找到的关卡Actor数组
	 */
	UFUNCTION(BlueprintCallable,Category="LevelToolPlugin|StreamingLevel", meta = (WorldContext = WorldContextObject))
	static bool GetLevelAllActorByLevelObject(const UObject* WorldContextObject,ULevel* Level, TArray<AActor*>&LevelActorTarray);
	
	

	/*
	 * Actor Can Attach Other Actor
	 * @InChildActor:						Child Actor,Will Attach Actor
	 * @InParentActor:						Parent Actor
	 * @return:								return Can Attach result
	 */
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="LevelToolPlugin|RuntimeLibrary|Actor")
	static bool bActorCanAttachOtherActor(const AActor* InChildActor,const AActor* InParentActor);









	

public:
	/*  Actor About   */
	
	/*
	 * Get World's Actor list
	 * @InLevel			Specified Worlds
	 * @return			Actor‘s TArray
	 */
	UFUNCTION(BlueprintCallable,Category = "LevelToolPlugin|RuntimeLibrary|Actor")
	static TArray<AActor*> GetLevelActorsByLevel(ULevel* InLevel);

	/*
	 * Get World's Group Actor
	 * @InWorld			Specified Worlds
	 * @return			Group Actor Array
	 */
	// UFUNCTION(BlueprintCallable,Category = "LevelToolPlugin|RuntimeLibrary|Actor")
	// static TArray<AActor*> GetWorldGroupActorsByWorld(UWorld* InWorld);

	/*
	 *MoveActor is need Actor filter,remove no move actor
	 * @ActorLevel				Actor所处的Level
	 * @DetectionActor			需要检测的Actor
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ToolPlugin|WorldOutLine|Folder", meta = (WorldContext = "WorldContextObject"))
		static bool MoveActorFilter(AActor* DetectionActor);

	/*
	 *MoveActor is need Actor filter,remove no move actor
	 * @ActorLevel				Actor所处的Level
	 * @DetectionActors			需要检测的Actors
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ToolPlugin|WorldOutLine|Folder", meta = (WorldContext = "WorldContextObject"))
		static bool MoveActorsFilter(TArray<AActor*> &DetectionActors);


	/*
	 *移动一个Actor到另一个Actor上
	 *@ParentActore				父Acrtor,子Actor挂载在父Actor上
	 *@ChildActor				子Actor
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LevelToolPlugin|WorldOutLine|Actor")
		static bool MoveChildActorAttachToParentActor(AActor* ParentActor, AActor* ChildActor);

	/*
	 *移动多个Actor到另一个Actor上
	 *@ParentActor				父Acrtor,子Actor挂载在父Actor上
	 *@ChildActors				子Actors
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LevelToolPlugin|WorldOutLine|Actor")
		static bool MoveChildActorsAttachToParentActor(AActor* ParentActor, TArray<AActor*> ChildActors);
	
	/*
	 *获取Actor在世界大纲中的路径
	 *@Actor					要获取文件路径的Actor
	 * return					成功返回true,否则false
	 */
	// UFUNCTION(BlueprintCallable, CallInEditor, BlueprintPure, Category = "LevelToolPlugin|WorldOutLine|Actor")
	// 	static FName GetActorFolderPath(AActor* Actor);

	/*
	 *在世界大纲中移动Actor到指定的文件夹
	 * @ParentFolderName		要移动到的文件夹
	 * @MoveActor				将要移动的Actor
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LevelToolPlugin|WorldOutLine|Actor")
		static bool MoveActorToFolder(const FName ParentFolderName, AActor* MoveActor);

	/*
	 *在世界大纲中移动多个Actor到指定的文件夹
	 * @ParentFolderName		要移动到的文件夹
	 * @MoveActors				将要移动的多个Actor
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LevelToolPlugin|WorldOutLine|Actor")
		static bool MoveActorsToFolder(const FName ParentFolderName, TArray<AActor*>MoveActors);
	
	/*
	 *在世界大纲中移动多个文件夹到到指定的文件夹下
	 * @ParentFolderName		父文件夹
	 * @ChildFolderNames		多个子文件夹
	 * return					成功返回true,否则false
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ToolPlugin|WorldOutLine|Folder", meta = (WorldContext = "WorldContextObject"))
		static bool MoveFoldersToFolder(const FName ParentFolderName, TArray<FName>ChildFolderNames, const UObject* WorldContextObject);

	/*
	 *检测字符串是不是包含数字与小数点
	 *@String					待检测的字符串
	 *return					成功返回true,否则false
	 */
	//String Wheather consists of Num Or decimal point
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ToolPlugin|WorldOutLine|Folder")
		static bool StringOnlyContainNumOrPoint(FString String);
	
















	
	////////////////////获取关卡内的内容_Start////////////////////////

	/*
	 * @InWorld 传入的World
	 * return 返回AActor数组
	 */
	UFUNCTION(BlueprintCallable,Category="ToolPlugin|World")
	static TArray<AActor*> GetSpecifyWorldActorsByWorld(const UWorld* InWorld);

	/*
	 * @InWorld 传入的Level
	 * return 返回AActor数组
	 */
	UFUNCTION(BlueprintCallable,Category="ToolPlugin|World")
	static TArray<AActor*> GetSpecifyWorldActorsByLevel(const ULevel* InLevel);

	/*
	 * @InWorld 传入的流关卡
	 * return 返回AActor数组
	 */
	UFUNCTION(BlueprintCallable,Category="ToolPlugin|World")
	static TArray<AActor*> GetSpecifyWorldActorsByLevelStreaming(const ULevelStreaming* InLevelStreaming);











	/* 获取当前运行的世界是编辑器模式下还是打包后的游戏模式下 */
	UFUNCTION(BlueprintCallable,Category="LevelToolPlugin|LevelCommonLib",meta=(WorldContext="WorldContextObject"))
	static ULevelToolCommonLibraryNameSpace::EWorldType GetCurrentWorldType(const UObject* WorldContextObject)
	{
		const UWorld* CurrentWorld=WorldContextObject->GetWorld();
		if (!CurrentWorld)
		{
			return ULevelToolCommonLibraryNameSpace::None;
		}
		else if (CurrentWorld->IsEditorWorld())
		{
			return ULevelToolCommonLibraryNameSpace::Eidtor;
		}
		else
		{
			return ULevelToolCommonLibraryNameSpace::Game;
		}
	}

#pragma region 设置流关卡的可视性
	//设置流关卡的可视性
	UFUNCTION(BlueprintCallable,Category = "LevelToolPlugin|LevelCommonLib",meta=(WorldContext="WorldContextObject"))
	static void SetStreamingLevelVisuality(const UObject* WorldContextObject,const TArray<TSoftObjectPtr<UWorld>>&ShowLevel,const TArray<TSoftObjectPtr<UWorld>>&HiddenLevel);

	//设置流关卡的可视性
	UFUNCTION(BlueprintCallable,Category = "LevelToolPlugin|LevelCommonLib",meta=(WorldContext="WorldContextObject"))
	static void SetStreamingLevelVisible(const UObject* WorldContextObject,const TSoftObjectPtr<UWorld> Level,bool Visible=false);

	//设置单个关卡的可见性
	UFUNCTION(BlueprintCallable,Category = "LevelToolPlugin|LevelCommonLib",meta=(WorldContext="WorldContextObject"))
	static void SetSingleLevelVisibility(const UObject* WorldContextObject,const TSoftObjectPtr<UWorld> InLevel,bool bEnableVisible=true);
#pragma endregion

	
};



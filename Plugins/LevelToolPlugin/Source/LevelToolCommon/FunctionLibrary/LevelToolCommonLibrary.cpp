// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelToolCommonLibrary.h"
#include "LevelToolCommon.h"
#include "Engine/LevelStreaming.h"

#if WITH_EDITOR
#include "Editor.h"

UWorld* ULevelToolCommonLibrary::GetEditorWorld()
{
	if (!GEditor)
	{
		UE_LOG(FLevelToolCommonLog,Warning,TEXT("GEditor is invalid"));
		return nullptr;
	}
	return  GEditor->GetEditorWorldContext().World();
}

#pragma region 子关卡状态
bool ULevelToolCommonLibrary::GetLevelVisualityInEditor(const TSoftObjectPtr<UWorld> Level, const UObject* WorldContextObject)
{
	//优先检测关卡是否有效
	if (!Level) return false;

	if (const ULevelStreaming* TemLevelStreaming=ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,Level))
	{
		return TemLevelStreaming->GetShouldBeVisibleInEditor();
	}
	return false;
}

bool ULevelToolCommonLibrary::IsAlwaysLoad(
	const TSoftObjectPtr<UWorld> Level,
	const UObject* WorldContextObject)
{
	//优先检测关卡是否有效
	if (!Level) return false;

	if (const ULevelStreaming* TemLevelStreaming=ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,Level))
	{
		return TemLevelStreaming->ShouldBeAlwaysLoaded();
	}	
	return false;
}



#pragma endregion


#endif

#pragma region 流关卡与UWorld之间转换
ULevelStreaming* ULevelToolCommonLibrary::GetStreamingLevel(const UObject* WorldContextObject,const TSoftObjectPtr<UWorld>& InWorld)
{
	//先检查传入的InWorld是否有效
	if (InWorld.IsNull()) return nullptr;
	
	TArray<ULevelStreaming*> LevelStreamings=GetWorldAllStreamingLevel(WorldContextObject);
	for (ULevelStreaming* TemStreamingLevel:LevelStreamings)
	{
		if (InWorld.GetAssetName()==GetStreamingLevelName(TemStreamingLevel))
		{
			return TemStreamingLevel;
		}
	}
	return nullptr;
}


TSoftObjectPtr<UWorld> ULevelToolCommonLibrary::GetUWorldPtr(const ULevelStreaming* StreamingLevel)
{
	if (!StreamingLevel)
	{
		UE_LOG(FLevelToolCommonLog,Warning,TEXT("StreamingLevel is invalid"));
		return nullptr;
	}
	return const_cast<TSoftObjectPtr<UWorld>&>(StreamingLevel->GetWorldAsset());
}
#pragma endregion

#pragma region UWorld中关卡的获取

ULevel* ULevelToolCommonLibrary::GetWorldPersistentLevel(UWorld* InWorld)
{
	if (!InWorld)
	{
		UE_LOG(FLevelToolCommonLog,Warning,TEXT("InWorld is invalid"));
		return nullptr;
	}
	return InWorld->PersistentLevel;
}

TArray<ULevelStreaming*> ULevelToolCommonLibrary::GetWorldAllStreamingLevel(const UObject* WorldContextObject)
{
	TArray<ULevelStreaming*>StreamingLevels;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		StreamingLevels=World->GetStreamingLevels();
		return StreamingLevels;
	}
	UE_LOG(FLevelToolCommonLog,Warning,TEXT("WorldContextObject is invalid"));
	return StreamingLevels;
}

TArray<ULevel*> ULevelToolCommonLibrary::GetWorldLevels(const TSoftObjectPtr<UWorld> InWorld)
{
	TArray<ULevel*> ReturnLevels;
	if (!InWorld) return ReturnLevels;

	return InWorld->GetLevels();
}


#pragma endregion

#pragma region 获取关卡信息
FString ULevelToolCommonLibrary::GetStreamingLevelName(const ULevelStreaming* StreamingLevel)
{
	//先检查
	if (!StreamingLevel) return FString();
	return  StreamingLevel->GetWorldAsset().GetAssetName();
}

FString ULevelToolCommonLibrary::GetLevelName(ULevel* InLevel, const bool bClearPrefix)
{
	if (InLevel)
	{
		if (bClearPrefix)
		{
			FString LeftStr(""),RightStr("");
			InLevel->GetPackage()->GetName().Split("/",&LeftStr,&RightStr,ESearchCase::IgnoreCase,ESearchDir::FromEnd);
			return RightStr;
		}
		return InLevel->GetOutermost()->GetName();
	}
	else
	{
		UE_LOG(FLevelToolCommonLog,Warning,TEXT("InLevel is invalid"));
		return FString();
	}
}

FName ULevelToolCommonLibrary::GetUWorldName(const TSoftObjectPtr<UWorld>& InWorld)
{
	if (!InWorld.IsNull())
	{
		if (*InWorld.GetAssetName())
		{
			return FName (*InWorld.GetAssetName());
		}
		UE_LOG(FLevelToolCommonLog,Warning,TEXT("InWorld.GetAssetName() is failed"));
		return FName();
	}
	UE_LOG(FLevelToolCommonLog,Warning,TEXT("InWorld is invalid"));
	return FName();
}


#pragma endregion



















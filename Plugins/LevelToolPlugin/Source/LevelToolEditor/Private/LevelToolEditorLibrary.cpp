// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/LevelToolEditorLibrary.h"
#include "../Public/LevelToolEditor.h"
#include "Editor.h"
#include "LevelToolCommon/FunctionLibrary/LevelToolCommonLibrary.h"
#include "EditorFramework/AssetImportData.h"

#ifndef FFILELINEINFO
#define FFILELINEINFO (FString(__FILE__)+FString("(")+FString::FromInt(__LINE__)+FString(") ")+FString(__FUNCTION__))
#endif
#pragma region 关卡引用


TArray<ULevel*> ULevelToolEditorLibrary::GetWorldCollectionLevels(const TSoftObjectPtr<UWorld> InWorld)
{
	TArray<ULevel*> ReturnLevels;
	if (!InWorld) return ReturnLevels;
	//TArray<FLevelCollection>LevelCollections=InWorld->GetLevelCollections();

	for (int i=0;i<InWorld->GetLevelCollections().Num();i++)
	{
		ReturnLevels.Add(InWorld->GetLevelCollections()[i].GetPersistentLevel());
	}

	return ReturnLevels;
}


#pragma endregion

bool ULevelToolEditorLibrary::GetStreamingLevelIsVisible(const ULevelStreaming* InLevelStreaming)
{
	if (!InLevelStreaming)
	{
		UE_LOG(FLevelToolEditorLog,Warning,TEXT("InLevelStreaming is invalid"));
		return false;
	}
	else
	{
		return InLevelStreaming->GetShouldBeVisibleInEditor();
	}
}

void ULevelToolEditorLibrary::ScaleScene(float ScaleValue, bool bScaleChildLevel,float ReferenceOriginTime)
{
	// FString AAA=FString::SanitizeFloat(ReferenceOriginTime);
	//
	// GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,*AAA);
	// UE_LOG(LogTemp,Warning,TEXT("ReferenceOriginTime IS:%s"),*AAA);
	//  if (bScaleChildLevel)
	//  {
	//  	//所有关卡
	//  	ScaleScenemultipleLevel(ScaleValue,ReferenceOriginTime);
	//  }else
	//  {
	//  	//当前关卡
	//  	ScaleSceneSingleLevel(ScaleValue,ReferenceOriginTime);
	// }
}

void ULevelToolEditorLibrary::ScaleSceneSingleLevel(float ScaleValue,float ReferenceOriginTime)
{
	// ULevel* CurrentLevelPersistentLevel;//获取当前世界优先级最高的首要关卡
	// if (ULevelToolRuntimeLibrary::GetWorldPersistendLevelByWorld(GetEditorWorld(),CurrentLevelPersistentLevel))
	// {
	// 	UE_LOG(LevelToolEditorLog,Warning,TEXT("Get PersistentLevel Is Invalid"));	
	// 	return;
	// }
	// ScaleLevelActors(CurrentLevelPersistentLevel,ScaleValue);
}

void ULevelToolEditorLibrary::ScaleScenemultipleLevel(float ScaleValue,float ReferenceOriginTime)
{
	// //获取Level
	// TArray<ULevel*> Levels;
	// //当前关卡
	// ULevel * CurrentPersistentLevel;
	// ULevelToolRuntimeLibrary::GetWorldPersistendLevelByWorld(GetEditorWorld(),CurrentPersistentLevel);
	// FString Name=CurrentPersistentLevel->GetName();
	// if (CurrentPersistentLevel!=nullptr)
	// {
	// 	Levels.Add(CurrentPersistentLevel);
	// }
	//
	// //当前关卡的流关卡
	// TArray<ULevelStreaming*>CurrentLevelSteamingLevels;
	// ULevelToolRuntimeLibrary::GetAllStreamingLevelObject(GetEditorWorld(),CurrentLevelSteamingLevels);
	//
	// //获取流关卡的ULevel
	// for (ULevelStreaming* TemLevelStreaming:CurrentLevelSteamingLevels)
	// {
	//
	// 	ULevel* NewTemLevel=ULevelToolRuntimeLibrary::GetULevelByStreamingObject(GEditor,TemLevelStreaming);
	// 	Levels.Add(NewTemLevel);
	// }
	//
	// //缩放Actor Core 方法
	// for (ULevel* TemLevel:Levels)
	// {
	// 	if (TemLevel!=nullptr)
	// 	{
	// 		ScaleLevelActors(TemLevel,ScaleValue);
	// 	}
	// }
	
}

void ULevelToolEditorLibrary::FilterOtherActors(TArray<AActor*>& SourceActors)
{
	TArray<AActor*>ResultActors;
	return	;
}

void ULevelToolEditorLibrary::ScaleLevelActors(ULevel* WillScaleLevel,const float ScaleValue)
{
	// //获取关卡内的Actor
	// TArray<AActor*>LevelInnerActors=ULevelToolRuntimeLibrary::GetLevelActorsByLevel(WillScaleLevel);
	// int Length=LevelInnerActors.Num();
	//
	//
	// //Filter Actor,Because have Actors can't move
	//  if (!ULevelToolRuntimeLibrary::MoveActorsFilter(LevelInnerActors))
	//  		return;
	//
	//  //在对应关卡创建一个Actor,no used Spawn Actor because Spawn Acotor function is actor in PersistentLevel
	//  ASceneOriginActor* TemSceneOriginActor=NewObject<ASceneOriginActor>(WillScaleLevel);
	//  TemSceneOriginActor->SetActorLocation(FVector(0.0f,0.0f,0.0f));
	//  TemSceneOriginActor->SetActorScale3D(FVector(1.0f,1.0f,1.0f));
	//
	//  TemSceneOriginActor->GetRootComponent()->SetMobility(EComponentMobility::Static);
	//
	//  TMap<AActor*,FName>ActorPaths;
	//  for (AActor* TemActor:LevelInnerActors)
	//  {
	//  	ActorPaths.Add(TemActor,TemActor->GetFolderPath());
	//  }
	//
	//
	//
	//  //挂载Actor
	//  ULevelToolRuntimeLibrary::MoveChildActorsAttachToParentActor(TemSceneOriginActor,LevelInnerActors);
	//
	//
	// //缩小
	// TemSceneOriginActor->SetActorScale3D(FVector(ScaleValue,ScaleValue,ScaleValue));
	//
	//  //Recover actor path in worldoutline
	//  for (AActor* TemActor:LevelInnerActors)
	//  {
	//  	//Detach Actor
	//  	//KeepRelativeTransform,Scale Will Reconver
	//  	TemActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//  	
	//  	//ReCover Actor Path
	//  	TemActor->SetFolderPath(*ActorPaths.Find(TemActor));
	//  }
	//
	//
	//  //Destory Actor
	//  TemSceneOriginActor->Destroy();
}

void ULevelToolEditorLibrary::SetUTextureMipGenSettings(UTexture* InUTexture)
{
	if (!InUTexture) return;
	InUTexture->MipGenSettings=TextureMipGenSettings::TMGS_NoMipmaps;
}

void ULevelToolEditorLibrary::SetUTextureLODGroup(UTexture* InUTexture)
{
	if (!InUTexture) return;
	InUTexture->LODGroup=TextureGroup::TEXTUREGROUP_UI;
}

void ULevelToolEditorLibrary::ClearUTexture2DSourceFile(UTexture* InUTexture)
{
	if (!InUTexture) return;
	InUTexture->AssetImportData.Get()->SourceData.SourceFiles.Empty();
}


////////////////////////////////////////Folder About//////////////////////////////////

bool ULevelToolEditorLibrary::GetWorldOutLineAllFolderByWorld(const UWorld* InWorld, TArray<FName>& ActorFolderNames)
{
	// //Actor Folders
	// FActorFolders SingletonActorFolders = FActorFolders::Get();
	//
	// if (!SingletonActorFolders.IsAvailable())
	// {
	// 	UE_LOG(LevelToolEditorLog, Warning, TEXT("SingletonActorFolders is invalid"));
	// 	return false;
	// }
	//
	// if (!InWorld)
	// {
	// 	UE_LOG(LevelToolEditorLog,Warning,TEXT("InWorld is In Valid,File:%s,Line:%d"),*(ANSI_TO_TCHAR(__FILE__)),__LINE__);
	// 	return false;
	// }
	//
	// TArray<FFolder>Folders;
	// TArray<FName>Names;
	// FFolder::FRootObject FolderRootObject;
	// FFolder::GetFolderPathsAndCommonRootObject(Folders,Names,FolderRootObject);
	// //TMap<FName, FActorFolderProps>TmapActorFolders = SingletonActorFolders.GetFolderPropertiesForWorld(*World);
	// //TmapActorFolders.GetKeys(ActorFolderNames);
	// ActorFolderNames=Names;
	return true;
}

bool ULevelToolEditorLibrary::CreateFolderInWorldOutline(UWorld* InWorld, const FName FolderName)
{
	// FActorFolders SingletonActorFolders = FActorFolders::Get();
	// if (!SingletonActorFolders.IsAvailable())
	// {
	// 	UE_LOG(LevelToolEditorLog, Warning, TEXT("SingletonActorFolders is invalid"));
	// 	return false;
	// }
	//
	// if (!InWorld->IsValidLowLevelFast())
	// {
	// 	UE_LOG(LevelToolEditorLog, Warning, TEXT("Get Editor World fail"));
	// 	return false;
	// }
	// //FolderName=FFolder::GetActorFolder().GetPath();
	// SingletonActorFolders.GetFolderProperties(*InWorld, FolderName);
	return true;
}

bool ULevelToolEditorLibrary::DeleteFolderInWorldOutline(UWorld* InWorld, FName FolderName)
{
	// FActorFolders SingletonActorFolders = FActorFolders::Get();
	// if (!SingletonActorFolders.IsAvailable())
	// {
	// 	UE_LOG(LevelToolEditorLog, Warning, TEXT("SingletonActorFolders is invalid"));
	// 	return false;
	// }
	//
	//
	//
	// if (!InWorld->IsValidLowLevelFast())
	// {
	// 	UE_LOG(LevelToolEditorLog, Warning, TEXT("Get Editor World fail"));
	// 	return false;
	// }
	
	//SingletonActorFolders.DeleteFolder(*InWorld, FolderName);
	return true;
}


//Move Folder Path
bool ULevelToolEditorLibrary::MoveFolderToFolder(const FName ParentFolderName, FName ChildFolderName, const UObject* WorldContextObject)
{
	// if (ParentFolderName == ChildFolderName)
	// {
	// 	UE_LOG(LevelToolEditorLog, Warning, TEXT("Not Move Folder To Folder,Because of Tha Same of Folder Name:ParentFolderName:%s,ChildFolderName:%s"), (*ParentFolderName.ToString()), *(ChildFolderName.ToString()));
	// 	return false;
	// }
	//Move Folder To Other Folder
	//SceneOutliner::MoveFolderTo(ChildFolderName, ParentFolderName, *GEngine->GetWorld());
	return true;
}



////////////////////////////////////////Folder About//////////////////////////////////


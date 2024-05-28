// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelToolRuntimeLibrary.h"

#include "GameFramework/PhysicsVolume.h"
#include "LevelToolRuntime.h"

#include "LevelToolCommon/FunctionLibrary/LevelToolCommonLibrary.h"


#include "GameFramework/WorldSettings.h"
#include "NavigationData.h"
#include "Engine/Brush.h"
#include "AbstractNavData.h"
#include "WorldPartition/DataLayer/WorldDataLayers.h"
#include "GameplayDebuggerPlayerManager.h"
#include "Engine/LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "WorldPartition/WorldPartitionMiniMap.h"
#include "ILevelToolManager.h"

























bool ULevelToolRuntimeLibrary::GetCurrentWorld(const UObject* WorldContextObject,UWorld*&RuntimeWorld)
{
	RuntimeWorld=GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!RuntimeWorld->IsValidLowLevel())
	{
		return false;
	}
	return true;
}

FVector ULevelToolRuntimeLibrary::GetChildLevelLocation(const UObject* WorldContextObject,
	TSoftObjectPtr<UWorld> InWorld)
{
	if (ULevelStreaming* LevelStreaming =ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,InWorld))
	{
		return LevelStreaming->LevelTransform.GetTranslation();
	}
	return FVector();
}

#pragma region 关卡变换
void ULevelToolRuntimeLibrary::SetChildLevelLocation(const UObject* WorldContextObject,TSoftObjectPtr<UWorld> InWorld, const FVector Location)
{
	if (ULevelStreaming* LevelStreaming = ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,InWorld))
	{
		LevelStreaming->LevelTransform.SetTranslation(Location);
	}
}

TArray<AActor*> ULevelToolRuntimeLibrary::GetLevelActorsBySoftWord(const UObject* WorldContextObject,
	TSoftObjectPtr<UWorld> InWorld)
{
	TArray<AActor*>ReturnArray;
	if (ULevelStreaming* LevelStreaming = ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,InWorld))
	{
		for (AActor* TemActor:InWorld->PersistentLevel.Get()->Actors)
		{
			if (TemActor->GetRootComponent()&&
				TemActor->GetRootComponent()->IsA<USceneComponent>()
				)
			{
				ReturnArray.Add(TemActor);
			}
		}
		
	}
	return ReturnArray;
}

#pragma endregion


TArray<AActor*> ULevelToolRuntimeLibrary::GetLevelActorsByLevel(ULevel* InLevel)
{
	if (InLevel)
	{
		return InLevel->Actors;
	}
	UE_LOG(FLevelToolRuntimeLog,Warning,TEXT("GetLevelActorsByLevel:InLevel is invalid"));
	return TArray<AActor*>();
}








FString ULevelToolRuntimeLibrary::GetStreamingLevelState(const ULevelStreaming* LevelStreaming)
{
	if (!LevelStreaming) return FString("");
	return EnumToString(LevelStreaming->GetLevelStreamingState());;
}

bool ULevelToolRuntimeLibrary::SingleLevelStateEqual(
	const ULevelStreaming* Level,
	const ELevelToolPluginLevelState LevelState)
{
	//优先检测关卡流对象是否有效
	if (!Level) return false;
	
	switch (LevelState)
	{
	case ELevelToolPluginLevelState::Removed:
		return Level->GetLevelStreamingState()==ELevelStreamingState::Removed;
	case ELevelToolPluginLevelState::Unloaded:
		return Level->GetLevelStreamingState()==ELevelStreamingState::Unloaded;
	case ELevelToolPluginLevelState::FailedToLoad:
		return Level->GetLevelStreamingState()==ELevelStreamingState::FailedToLoad;
	case ELevelToolPluginLevelState::Loading:
		return Level->GetLevelStreamingState()==ELevelStreamingState::Loading;
	case ELevelToolPluginLevelState::LoadedNotVisible:
		return Level->GetLevelStreamingState()==ELevelStreamingState::LoadedNotVisible;
	case ELevelToolPluginLevelState::MakingVisible:
		return Level->GetLevelStreamingState()==ELevelStreamingState::MakingVisible;
	case ELevelToolPluginLevelState::LoadedVisible:
		return Level->GetLevelStreamingState()==ELevelStreamingState::LoadedVisible;
	case ELevelToolPluginLevelState::MakingInvisible:
		return Level->GetLevelStreamingState()==ELevelStreamingState::MakingInvisible;
	default:
		return false;
	}
}

bool ULevelToolRuntimeLibrary::MultileLevelStateEqual(const TArray<ULevelStreaming*> Levels,
	const ELevelToolPluginLevelState LevelState)
{
	const ELevelStreamingState State= ULevelToolPlugin::CastELevelToolPluginLevelStateToELevelStreamingState(LevelState);
	for (const ULevelStreaming* TemLevelStreaming:Levels)
	{
		//优先检测是否有效
		if (!TemLevelStreaming) return false;

		//如果状态不等,跳出循环返回false,否则进行下一次循环
		if (TemLevelStreaming->GetLevelStreamingState()!=State) return false;
	}
	//所有关卡的状态都相等则返回true
	return true;
}


ULevel* ULevelToolRuntimeLibrary::GetULevelByStreamingObject(const UObject* WorldContextObject,
                                                             ULevelStreaming* LevelStreaming)
{
	//获取流关卡的主关卡
	if (LevelStreaming)
	{
		if (LevelStreaming->GetWorldAsset()->IsValidLowLevel())
		{
			ULevel* TemLevel=LevelStreaming->GetWorldAsset().Get()->PersistentLevel;
			return TemLevel;
		}
	}
	return NewObject<ULevel>();
}

bool ULevelToolRuntimeLibrary::GetLevelAllActorByLevelObject(const UObject* WorldContextObject,ULevel* Level, TArray<AActor*>& LevelActorTarray)
{
	if(!Level)
		return false;

	LevelActorTarray=Level->Actors;
	return true;
}

bool ULevelToolRuntimeLibrary::bActorCanAttachOtherActor(const AActor* InChildActor, const AActor* InParentActor)
{
	//Check Attach Actor can To Other Actors
	//1.if(ChildActor == NULL || ParentActor == NULL)
	//2.if(ChildActor == ParentActor)
	//3.if (ChildActor->GetRootComponent() == NULL || ParentActor->GetDefaultAttachComponent() == NULL)
	//4.if ((Cast<const  ABrush >(ParentActor) && !(Cast<const  ABrush >(ParentActor))->IsVolumeBrush()) || (Cast<const  ABrush >(ChildActor) && !(Cast<const  ABrush >(ChildActor))->IsVolumeBrush()))
	//5.if (ChildRoot->Mobility == EComponentMobility::Static && ParentRoot->Mobility != EComponentMobility::Static)
	//6.if(ChildActor->GetLevel() != ParentActor->GetLevel())
	//7.if(ParentRoot->IsAttachedTo( ChildRoot ))
	if (InChildActor==nullptr||InParentActor==nullptr)
	{
		return false;
	}else if (InChildActor==InParentActor)
	{
		return false;
	}else if (InChildActor->GetRootComponent()==nullptr||
		InParentActor->GetRootComponent()==nullptr)
	{
		return false;
	}else if ((Cast<const ABrush>(InParentActor)&&!Cast<const ABrush>(InParentActor)->IsVolumeBrush())||
		((Cast<const ABrush>(InChildActor)&&!Cast<const ABrush>(InChildActor)->IsVolumeBrush())))
	{
		return false;
	}else if (InChildActor->GetRootComponent()->Mobility==EComponentMobility::Static &&
		InParentActor->GetRootComponent()->Mobility!=EComponentMobility::Static)
	{
		return false;
	}else if (InChildActor->GetLevel()!=InParentActor->GetLevel())
	{
		return false;
	}else if (InParentActor->GetRootComponent()->IsAttachedTo(InChildActor->GetRootComponent()))
	{
		return false;
	}
	return true;
}









bool ULevelToolRuntimeLibrary::MoveChildActorAttachToParentActor(AActor* ParentActor, AActor* ChildActor)
{
	//Ensure ChildActor is valid
	if (!ChildActor->IsValidLowLevelFast())
	{
		UE_LOG(FLevelToolRuntimeLog, Warning, TEXT("%s:The Child Actor is nullptr"), *(ChildActor->GetName()));
		return false;
	}
	
	//Ensure ParentActor is valid
	if (!ParentActor->IsValidLowLevelFast())
	{
		UE_LOG(FLevelToolRuntimeLog, Warning, TEXT("%s:Parent Actor is nullptr"), *ParentActor->GetName());
		return false;
	}
	
	if (ChildActor->GetParentActor())
	{
		//有父Actor的Actor不需要移动
		UE_LOG(FLevelToolRuntimeLog, Display, TEXT("%s:The Child Actor Has Parent Actor ,No Need Move"), *(ChildActor->GetName()));
		return false;
	}

	if (ChildActor->GetClass()==AWorldDataLayers::StaticClass()||
		ChildActor->GetClass()==AGameplayDebuggerPlayerManager::StaticClass()||
		ChildActor->GetClass()==AWorldPartitionMiniMap::StaticClass()
		)
				return false;
	
	//Initialize childActor mobility,Use to reserve child actor mobility
	const TEnumAsByte<EComponentMobility::Type> ChildActorMobility = ChildActor->GetRootComponent()->Mobility;
	//const EComponentMobility::Type ChildActorMobility = ChildActor->GetRootComponent()->Mobility;
	
	//If ChildActor Mobility is static,Parent Actor Mobility must is static,else will not call
	if (ChildActorMobility == EComponentMobility::Static)
	{
		if (ParentActor->GetRootComponent()->Mobility != EComponentMobility::Static)
		{
			//ParentActorMobility = ParentActor->GetRootComponent()->Mobility;
			ParentActor->GetRootComponent()->SetMobility(EComponentMobility::Static);
		}
	}

	//Check Attach Actor can To Other Actors
	//1.if(ChildActor == NULL || ParentActor == NULL)
	//2.if(ChildActor == ParentActor)
	//3.if (ChildActor->GetRootComponent() == NULL || ParentActor->GetDefaultAttachComponent() == NULL)
	//4.if ((Cast<const  ABrush >(ParentActor) && !(Cast<const  ABrush >(ParentActor))->IsVolumeBrush()) || (Cast<const  ABrush >(ChildActor) && !(Cast<const  ABrush >(ChildActor))->IsVolumeBrush()))
	//5.if (ChildRoot->Mobility == EComponentMobility::Static && ParentRoot->Mobility != EComponentMobility::Static)
	//6.if(ChildActor->GetLevel() != ParentActor->GetLevel())
	//7.if(ParentRoot->IsAttachedTo( ChildRoot ))

	if (bActorCanAttachOtherActor(ChildActor,ParentActor))
	{
		//ChildActor Attach To ParentActor and Change ChildActor FolderPath 
		//Core Operation is "Actor->AttachToComponent"
		ChildActor->AttachToActor(ParentActor,FAttachmentTransformRules::KeepRelativeTransform,FName());
		//GEditor->ParentActors(ParentActor, ChildActor, FName());

		//分离出现问题
		//ChildActor->SetFolderPath_Recursively(ParentActor->GetFolderPath());

		//Reserve ChildActor Mobility
		ChildActor->GetRootComponent()->SetMobility(ChildActorMobility);
		return true;
	}
	//Can't move,because of CanParentActors is return false
	UE_LOG(FLevelToolRuntimeLog, Warning, TEXT("ParentActor:%s,ChildAcror:%s :CanParentActors return false,Can't move"), *ParentActor->GetName(), *ChildActor->GetName());
	return false;
}

bool ULevelToolRuntimeLibrary::MoveChildActorsAttachToParentActor(AActor* ParentActor, TArray<AActor*> ChildActors)
{
	for (AActor* TemChildActor : ChildActors)
	{
		MoveChildActorAttachToParentActor(ParentActor, TemChildActor);
	}
	return true;
}

//Actor Folder Path
// FName ULevelToolRuntimeLibrary::GetActorFolderPath(AActor* Actor)
// {
// 	if (Actor)
// 	{
// 		return Actor->GetFolderPath();
// 	}
// 	return FName();
// }

bool ULevelToolRuntimeLibrary::MoveActorToFolder(const FName FoldeName, AActor* MoveActor)
{
	// TSubclassOf<AActor>OriginActorClass = LoadClass<AActor>(NULL, TEXT("Blueprint'/ToolPlugins/ToolActor_BP.ToolActor_BP_C'"));
	// if (!MoveActor->GetParentActor())
	// {
	// 	MoveActor->SetFolderPath(FoldeName);
	// 	return true;
	// }
	// else if (MoveActor->GetAttachParentActor()->GetClass() == OriginActorClass)
	// {
	// 	//1.Detach Actor From Parent Actor
	// 	MoveActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//
	// 	UE_LOG(LevelToolPluginLog, Warning, TEXT("%s has DetachFromActor"), *(MoveActor->GetName()));
	//
	// 	//MoveActor is in the root
	// 	//2.Set Actor Folder Path
	// 	MoveActor->SetFolderPath(FoldeName);
	// 	//MoveActor->Modify();
	// 	return true;
	// }
	// UE_LOG(LevelToolPluginLog, Error, TEXT("%s:  Is not Attach Special Actor"), *(MoveActor->GetName()));
	return false;
}

bool ULevelToolRuntimeLibrary::MoveActorsToFolder(const FName FoldeName, TArray<AActor*> MoveActors)
{
	if (MoveActors.Num() != 0)
	{
		for (AActor* TemChildActor : MoveActors)
		{
			MoveActorToFolder(FoldeName, TemChildActor);
		}
		return true;
	}
	return false;
}


bool ULevelToolRuntimeLibrary::MoveActorFilter(AActor* DetectionActor)
{
	if (DetectionActor)
	{
		if (
			DetectionActor->GetClass() == AWorldSettings::StaticClass() ||
			DetectionActor->GetClass() == APhysicsVolume::StaticClass() ||
			DetectionActor->GetClass() == ANavigationData::StaticClass() ||
			DetectionActor->GetClass() == ABrush::StaticClass() ||
			DetectionActor->GetClass() == AAbstractNavData::StaticClass()||
			DetectionActor->GetClass() == ALevelScriptActor::StaticClass())
		{
			UE_LOG(FLevelToolRuntimeLog, Display, TEXT("%s: The Actor can't move"), *(DetectionActor->GetName()));
			return false;
		}
		
		// if(Cast<ALevelScriptActor>(DetectionActor) ==DetectionActor->GetWorld()->PersistentLevel->GetLevelScriptActor())
		// {
		// 	UE_LOG(FLevelToolRuntimeLog, Display, TEXT("%s: LevelScript Actor can't move"), *(DetectionActor->GetName()));
		// 	return false;
		// }

		if (DetectionActor->GetParentActor()!=nullptr||
			DetectionActor->GetAttachParentActor()!=nullptr||
			DetectionActor->GetParentComponent()!=nullptr
			)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool ULevelToolRuntimeLibrary::MoveActorsFilter(TArray<AActor*> &DetectionActors)
{
	TArray<AActor*>StandardActors;
	if (DetectionActors.Num()!=0)
	{
		for (AActor* TemActor:DetectionActors)
		{
			if (MoveActorFilter(TemActor))
			{
				StandardActors.Add(TemActor);
			}
		}
		DetectionActors=StandardActors;
		return true;
	}
	return false;
}

bool ULevelToolRuntimeLibrary::MoveFoldersToFolder(const FName ParentFolderName, TArray<FName> ChildFolderNames, const UObject* WorldContextObject)
{
	if (ChildFolderNames.Num() == 0)
	{
		UE_LOG(FLevelToolRuntimeLog, Warning, TEXT("Not Move Folder To Folder,Because of The ChildFolderNames Tarray Length =0:%d"), __LINE__);
		return false;
	}
	return true;
}

bool ULevelToolRuntimeLibrary::StringOnlyContainNumOrPoint(FString String)
{
	//FString::SanitizeFloat
	return true;
}

TArray<AActor*> ULevelToolRuntimeLibrary::GetSpecifyWorldActorsByWorld(const UWorld* InWorld)
{
	TArray<AActor*> TemActors=InWorld->PersistentLevel->Actors;
	return TemActors;
}

TArray<AActor*> ULevelToolRuntimeLibrary::GetSpecifyWorldActorsByLevel(const ULevel* InLevel)
{
	TArray<AActor*> TemActors=InLevel->Actors;
	return TemActors;
}

TArray<AActor*> ULevelToolRuntimeLibrary::GetSpecifyWorldActorsByLevelStreaming(const ULevelStreaming* InLevelStreaming)
{
	TArray<AActor*> TemActors=InLevelStreaming->GetWorldAsset().Get()->PersistentLevel->Actors;
	return TemActors;
}

















void ULevelToolRuntimeLibrary::SetStreamingLevelVisuality(const UObject* WorldContextObject,const TArray<TSoftObjectPtr<UWorld>>& ShowLevel,
	const TArray<TSoftObjectPtr<UWorld>>& HiddenLevel)
{
	for (TSoftObjectPtr<UWorld>TemLevel :ShowLevel)
	{
		//检查关卡对象是否有效
		if (!(TemLevel.Get()->IsValidLowLevelFast())) continue;

		if (ULevelStreaming* TemLevelStreaming= ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,TemLevel))
		{
			TemLevelStreaming->SetShouldBeVisible(true);
		}
	}

	for (TSoftObjectPtr<UWorld>TemLevel :HiddenLevel)
    	{
    		//检查关卡对象是否有效
    		if (!(TemLevel.Get()->IsValidLowLevelFast())) continue;
    
    		if (ULevelStreaming* TemLevelStreaming= ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,TemLevel))
    		{
    			TemLevelStreaming->SetShouldBeVisible(false);
    		}
    	}
	
}

void ULevelToolRuntimeLibrary::SetStreamingLevelVisible(const UObject* WorldContextObject,
	const TSoftObjectPtr<UWorld> Level,bool Visible)
{
	//检查关卡对象是否有效
	if (!Level.Get()->IsValidLowLevelFast()) return;

	if (ULevelStreaming* TemLevelStreaming= ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,Level))
	{
		TemLevelStreaming->SetShouldBeVisible(Visible);
	}
	
}

void ULevelToolRuntimeLibrary::SetSingleLevelVisibility(const UObject* WorldContextObject,
	const TSoftObjectPtr<UWorld> InLevel, bool bEnableVisible)
{
	//检查关卡对象是否有效
	if (!InLevel.Get()->IsValidLowLevelFast()) return;

	if (ULevelStreaming* TemLevelStreaming= ULevelToolCommonLibrary::GetStreamingLevel(WorldContextObject,InLevel))
	{
		TemLevelStreaming->SetShouldBeVisible(bEnableVisible);
	}
}



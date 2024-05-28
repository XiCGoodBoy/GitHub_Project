// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelToolSubsystem.h"

/* CreateWidget function need this head file */
#include "Blueprint/UserWidget.h"
/* Get post login delegate need this head file */
#include "GameFramework/GameModeBase.h"
#include "LevelToolRuntime.h"
/* Get custom project setting need this head file for create default object */
#include "ILevelToolManager.h"
#include "../Type/LevelConfigData.h"
#include "../UI/LevelLoadBaseWidget.h"
#include "LevelToolSettings.h"



bool ULevelToolSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	const ULevelToolSettings* LevelToolSettings= ULevelToolSettings::GetLevelToolCommonSetting();

	//确保LevelToolSettings有效
	if (!LevelToolSettings)
	{
		Load_Level_End.Broadcast();
		return false;
	}
	
	
	//检查是否在项目设置中开启bEnable_Start_Level_Load
	if (ULevelToolSettings::GetLevelToolCommonSetting()->bEnable_Start_Level_Load==false)
	{
		Load_Level_End.Broadcast();
		return false;
	}

	//检查UI类型是否有效
	if (!ULevelToolSettings::GetLevelToolCommonSetting()->Level_Load_UI_Class.Get())
	{
		Load_Level_End.Broadcast();
		return false;
	}
	
	//检查加载关卡要读取的配置是否为我们想要的类型
	const ULevelArrayData* LevelArrayData=Cast<ULevelArrayData>(ULevelToolSettings::GetLevelToolCommonSetting()->Level_Load_Config_Data.LoadSynchronous());
	if (!LevelArrayData)
	{
		Load_Level_End.Broadcast();
		return false;
	}
	
	//检查要加载的关卡数量是否为0
	if (LevelArrayData->VisibleLevels.Num()==0&&
		LevelArrayData->NoVisibleLevels.Num()==0)
	{
    	Load_Level_End.Broadcast();
    	return false;
    }
	
	return true;
}

void ULevelToolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	//绑定委托在GameModeBase加载完毕之后调用
	FGameModeEvents::OnGameModePostLoginEvent().AddUObject(this,&ULevelToolSubsystem::CreateLoadLevelUI);
	
}

void ULevelToolSubsystem::CreateLoadLevelUI(AGameModeBase* GameModeBase,APlayerController* PlayerController)
{
	//创建UI
	Level_Load_UI=CreateWidget<ULevelLoadBaseWidget>(PlayerController,ULevelToolSettings::GetLevelToolCommonSetting()->Level_Load_UI_Class);
	
	//加载加载关卡UI的背景图片
	UTexture2D* BackgroundTexture=ILevelToolManager::Get()->GetLevelLoadBackgroundImage();
	
	//为UI设置图片
	if (BackgroundTexture)
	{
		Level_Load_UI->Level_Load_Background_Image->SetBrushFromTexture(BackgroundTexture);
	}
	else
	{
		Level_Load_UI->Level_Load_Background_Image->SetBrushTintColor(FSlateColor(FColor::Black));
		UE_LOG(FLevelToolRuntimeLog,Warning,TEXT("BackgroundTexture无效"));
	}

	//将UI添加到视口
	Level_Load_UI->AddToViewport(ULevelToolSettings::GetLevelToolCommonSetting()->Level_Load_Z_Order);

	//创建ALevelToolCompoentActorActor,用于加载关卡实现
    LevelToolCompoentActor=PlayerController->GetWorld()->SpawnActor<ALevelToolCompoentActor>();
    LevelToolComponent = LevelToolCompoentActor->LevelToolComponent;
	
	//绑定加载关卡进度委托
	FScriptDelegate LevelToolPercentDelegate;
	LevelToolPercentDelegate.BindUFunction(this,TEXT("Level_Load_Percent_Internal"));
	LevelToolComponent->Update_Load_Level_Progress_Delegate.Add(LevelToolPercentDelegate);
	
	//绑定加载关卡完毕委托
	FScriptDelegate LevelToolCompleteScriptDelegate;
	LevelToolCompleteScriptDelegate.BindUFunction(this,TEXT("Level_Load_Complete_Internal"));
	LevelToolComponent->EndLevelLoadDelegate.Add(LevelToolCompleteScriptDelegate);
	
	//委托已经绑定完毕,此时可以开始加载关卡了
	LevelToolComponent->Load_Mul_Level(
		Cast<ULevelArrayData>(ULevelToolSettings::GetLevelToolCommonSetting()->Level_Load_Config_Data.LoadSynchronous())->VisibleLevels,
		Cast<ULevelArrayData>(ULevelToolSettings::GetLevelToolCommonSetting()->Level_Load_Config_Data.LoadSynchronous())->NoVisibleLevels);
}

void ULevelToolSubsystem::Level_Load_Percent_Internal(const float Percent)const
{
	Load_Level_Progress.Broadcast(Percent);
	
	//检查UI是否有效
	if (!Level_Load_UI) return;

	//检查UI的Level_Load_Progress_Text是否有效
	if (!Level_Load_UI->Level_Load_Progress_Text) return;

	//更细UI的加载进度显示
	Level_Load_UI->Update_Level_Load_Progress_Text(Percent);
}

void ULevelToolSubsystem::Level_Load_Complete_Internal()
{
	Load_Level_End.Broadcast();
	
	//检查UI是否有效
	if (!Level_Load_UI) return;

	//移除UI并清空
	Level_Load_UI->RemoveFromParent();
	Level_Load_UI=nullptr;

	//检查LevelToolComponent是否有效
	if (!LevelToolComponent) return;

	//置为空,并销毁Actor
	LevelToolComponent=nullptr;
	LevelToolCompoentActor->Destroy();
	LevelToolCompoentActor=nullptr;
}



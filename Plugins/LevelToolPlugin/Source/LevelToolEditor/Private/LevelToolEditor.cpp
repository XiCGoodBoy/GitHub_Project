// Copyright Epic Games, Inc. All Rights Reserved.
#include "LevelToolEditor.h"
//Slate样式所需的头文件
#include "Styling/SlateStyle.h"
//注册Slate样式所需的头文件
#include "Styling/SlateStyleRegistry.h"
//查找插件路径所需的头文件
#include "Interfaces/IPluginManager.h"
//
#include "LevelToolEditorCommands.h"
//弹出文件对话框
#include "Misc/MessageDialog.h"

#include "../Public/LevelToolEditorWidget.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"

DEFINE_LOG_CATEGORY(FLevelToolEditorLog);
#define LOCTEXT_NAMESPACE "FLevelScalePuginModule"



//定义样式集的名称
FName SlateStyleSetName(TEXT("LevelToolSlateStyleSetName"));
//定义图片样式的名称
FName ImageStyleName(TEXT("LevelToolButtonImageStyle"));
//定义按钮样式要使用的图片名称
FName ImageName(TEXT("ButtonIcon_40x.png"));

static const FName LevelToolEditorTabName("LevelToolEditor");
const FText WindowsName=LOCTEXT("关卡编辑器工具", "关卡缩放工具");

void FLevelToolEditorModule::StartupModule()
{
	// //初始化注册Slate样式
	// if (!LevelToolEditorSlateStyleSet.IsValid())
	// {
	// 	//创建一个共享指针对象
	// 	LevelToolEditorSlateStyleSet= MakeShareable(new FSlateStyleSet(SlateStyleSetName));
	// 	
	// 	//插件根目录下的Resource文件夹路径
	// 	const FString ResourcesPath=FPaths::ConvertRelativePathToFull(IPluginManager::Get().FindPlugin("LevelToolPlugin")->GetBaseDir() / TEXT("Resources"));
	// 	
	// 	//使用Set方法创建一个样式并添加到样式集中
	// 	LevelToolEditorSlateStyleSet->Set(
	// 		ImageStyleName,
	// 		new FSlateImageBrush(
	// 			(ResourcesPath+FString("/")+ImageName.ToString()),
	// 			FVector2D(16.0f,16.0f)));
	// 	
	// 	//注册定义的样式
	// 	FSlateStyleRegistry::RegisterSlateStyle(*LevelToolEditorSlateStyleSet.Get());
	// }
	//
	// //注册命令
	// FLevelToolEditorCommands::Register();
	//
	// //创建FUICommandList,FUICommandList将FUICommandInfo和FUIAction联系起来
	// LevelToolEitorCommands = MakeShareable(new FUICommandList);
	//
	// //映射行为,将LevelToolEditorCommonInfo和实际行为连接起来
	// LevelToolEitorCommands->MapAction(
	// 	FLevelToolEditorCommands::Get().LevelToolEditorCommonInfo,
	// 	FExecuteAction::CreateLambda
	// 	(
	// 		[=]()
	// 		{
	// 			LevelToolEditorButtonClicked();
	// 		}
	// 	),
	// 	FCanExecuteAction());

	//注册启动回调
	//UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLevelToolEditorModule::RegisterMenus));
}

void FLevelToolEditorModule::ShutdownModule()
{




	
	//UToolMenus::UnRegisterStartupCallback(this);

	//UToolMenus::UnregisterOwner(this);

	
	// //取消命令注册
	// FLevelToolEditorCommands::Unregister();
	//
	// //从库中移除注册的样式
	// FSlateStyleRegistry::UnRegisterSlateStyle(*LevelToolEditorSlateStyleSet.Get());
	// LevelToolEditorSlateStyleSet.Reset();
}

// void FLevelToolEditorModule::LevelToolEditorButtonClicked()
// {
//
// 	FMessageDialog::Open(EAppMsgType::Ok,NSLOCTEXT("LevelToolEditor","Test","Test LevelToolEditorButtonClicked"));
// 	// if (!TestDockTab.IsValid())
// 	// {
// 	// 	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(LevelToolEditorTabName, FOnSpawnTab::CreateRaw(this, &FLevelToolEditorModule::OnSpawnPluginTab));
// 	// }
// 	// FGlobalTabmanager::Get()->TryInvokeTab(LevelToolEditorTabName);
// }
//
// void FLevelToolEditorModule::RegisterMenus()
// {
// 	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
// 	//FToolMenuOwnerScoped OwnerScoped(this);
// 	
// 	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
// 	{
// 		FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
// 		Section.AddMenuEntryWithCommandList(FLevelToolEditorCommands::Get().LevelToolEditorCommonInfo, LevelToolEitorCommands);
// 	}
//
// 	{
// 		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
// 		{
// 			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
// 			{
// 				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FLevelToolEditorCommands::Get().LevelToolEditorCommonInfo));
// 				Entry.SetCommandList(LevelToolEitorCommands);
// 			}
// 		}
// 	}
// }
//
// const ISlateStyle& FLevelToolEditorModule::GetSlateStyle()
// {
// 	return *LevelToolEditorSlateStyleSet.Get();
// }
//
// FName FLevelToolEditorModule::GetStyleSetName()
// {
// 	return SlateStyleSetName;
// }

// TSharedRef<SDockTab> FLevelToolEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& InSpawnTabArgs)
// {
// 	return SAssignNew(TestDockTab,SDockTab)
// 		.TabRole(ETabRole::NomadTab)
// 		.Label(WindowsName)
// 		.ToolTipText(WindowsName)
// 		.OnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this,&FLevelToolEditorModule::OnTabClosed))
// 		.Clipping(EWidgetClipping::ClipToBounds)
// 		[
// 			SNew(SLevelToolEditorWidget)
// 		];
// }

// void FLevelToolEditorModule::OnTabClosed(TSharedRef<SDockTab> InTab)
// {
// 	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LevelToolEditorTabName);
// 	TestDockTab.Reset();
// }


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLevelToolEditorModule, LevelToolEditor)
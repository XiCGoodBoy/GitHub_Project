#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

DECLARE_LOG_CATEGORY_EXTERN(FLevelToolEditorLog,Log,All);

class FLevelToolEditorModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
	
    //当点击按钮时调用
    //void LevelToolEditorButtonClicked();
private:
	//定义FUICommandList,定义FUICommandList将一个FUICommandInfo与一个FUIAction（命令具体实施的操作）对应起来
	//TSharedPtr<class FUICommandList> LevelToolEitorCommands;



	
	//void RegisterMenus();
    // TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& InSpawnTabArgs);
    // void OnTabClosed(TSharedRef<SDockTab> InTab);

	
	
    // TSharedPtr<class SWindow> LevelScaleWindow;
    // TSharedPtr<SDockTab> TestDockTab;

public:
	//获取Slate样式
	//static const ISlateStyle& GetSlateStyle();

	//获取Slate样式名
	//static FName GetStyleSetName();

	//样式集,用以储存创建的样式
	//static inline TSharedPtr<FSlateStyleSet> LevelToolEditorSlateStyleSet=nullptr;



	
};

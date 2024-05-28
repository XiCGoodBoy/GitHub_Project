// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Layout/SGridPanel.h"
/**
 * 
 */
class LEVELTOOLEDITOR_API SLevelToolEditorWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLevelToolEditorWidget)
		{
		}
	SLATE_END_ARGS()
	
	//创建小控件
	void Construct(const FArguments& InArgs);
	TSharedPtr<SNotificationList> GetNotificationListPtr()const;

	void SetScaleTimes(float InScaleTime);
	void SetReferenceOriginTime(float Times);

	



	
	/*
	 * 获取是否勾选缩放子关卡复选框信息
	 * @State			传入的复选框状态信息
	 */
	void GetCheckState(ECheckBoxState State);

	/*
	 *Create Single Selecte Level UI Entry
	 *@return SNew<SHorizontalBox>Entry
	 */
	//TSharedRef<SHorizontalBox> CreateSelecteItem(FName ItemName);
	void SelecteLevelItem();








	/* Item Dictionary */
	TMap<FName,UObject*>ItemDictionary;



	//构建一个条目,条目有一个复选框+流关卡名
	TSharedPtr<SHorizontalBox> CreateLevelItemEvent(const FName LevelName);

	//选中的关卡名
	TArray<FName>SelectLevelName;

	void CheckBoxStateChange(ECheckBoxState CheckBoxState);
	
private:
	/** The list of active system messages */
	//TSharedPtr<SNotificationList> NotificationListPtr;
	// TArray<FHotPatcherCategory> CategoryPages;
	//TSharedPtr<SVersionUpdaterWidget> VersionUpdaterWidget;
	TSharedPtr<SGridPanel> ActionPageGridPanel;

	//当前的缩放倍数,一般默认为1
	float CurrentScaleTime=1.0f;
	//最终的缩放倍数,默认为1
	float ScaleTimes=1.0f;
	//缩放子关卡,为true时将缩放首要关卡和额外的子关卡,为false时只缩放首要关卡
	bool bScaleChildLevel=false;

	
	//参考场景原点倍数
	float ReferenceOriginTime=1.0f;
	//场景缩放
	FReply OnClickScaleLevelButton()const;
};


//声明一个Slate条目,条目结构为:复选框+名称
class LEVELTOOLEDITOR_API SCheckBoxNameItemWidget : public SCompoundWidget
{
	
	SLATE_BEGIN_ARGS(SCheckBoxNameItemWidget)
		{}
		SLATE_ARGUMENT(FName,ItemName)
		SLATE_ARGUMENT(ECheckBoxState,StartCheckBoxState)
	SLATE_END_ARGS()

	//条目名,应以存储信息
	FName ItemName;
	//复选框状态
	ECheckBoxState CheckBoxState;

	//构造函数
	void Construct(const FArguments& InArgs)
	{
		this->ItemName=InArgs._ItemName;
		this->CheckBoxState=InArgs._StartCheckBoxState;

		
		//构造UI
		ChildSlot
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			[
				SNew(SCheckBox)
				.IsChecked(CheckBoxState)
				.OnCheckStateChanged(this,&SCheckBoxNameItemWidget::OnCheckBoxStateChangeEvent)
			]
			+SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(FText::FromName(ItemName))
			]
		];
	}

	//当复选框状态改变时通知当前控件的状态
	void OnCheckBoxStateChangeEvent(ECheckBoxState InCheckBoxState)
	{
		CheckBoxState=InCheckBoxState;
	}
	
};










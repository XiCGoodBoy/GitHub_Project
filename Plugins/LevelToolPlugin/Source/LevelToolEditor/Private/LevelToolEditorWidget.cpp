// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/LevelToolEditorWidget.h"
#include "LevelToolEditorLibrary.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SEditableText.h"
//include "Widgets/Input/SSpinBox.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SLevelToolEditorWidget::Construct(const FArguments& InArgs)
{
	// ChildSlot
	// [
	// 	//构建一个Border
	// 	SNew(SBorder)
	// 	[
	// 		SNew()
	// 	]
	// ];
}

void SLevelToolEditorWidget::SetScaleTimes(float InScaleTime)
{
	ScaleTimes=InScaleTime;
}

void SLevelToolEditorWidget::SetReferenceOriginTime(float Times)
{
	ReferenceOriginTime=Times;
}

void SLevelToolEditorWidget::GetCheckState(ECheckBoxState State)
{
	switch (State)
	{
	case ECheckBoxState::Checked:
		bScaleChildLevel=true;
		break;
	case ECheckBoxState::Unchecked:
		bScaleChildLevel=false;
		break;
	case ECheckBoxState::Undetermined:
		bScaleChildLevel=false;
		break;
	default:
		break;
	}





	
	// if (State==ECheckBoxState::Checked)
	// {
	// 	ItemDictionary.Empty();
	// 	TArray<ULevelStreaming*> TemStreamingLevels;
	// 	
	// 	if (ULevelToolRuntimeLibrary::GetAllStreamingLevelObject(ULevelToolEditorLibrary::GetEditorWorld(),TemStreamingLevels))
	// 	{
	// 		for (ULevelStreaming* Tem:TemStreamingLevels)
	// 		{
	// 			ItemDictionary.Add(FName(*ULevelToolRuntimeLibrary::GetStreamingLevelName(Tem)),Tem);
	// 		}
	// 		
	// 	//Start Create Selecte Level List
	// 		
	//
	//
	// 		
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp,Warning,TEXT("Can't Create Select Level List,because of Get Sub Streaming Level Fail"));
	// 	}
	// 	
	// 	
	// }
	// else
	// {
	// 	//销毁创建的流关卡列表
	// 	
	// 	
	// }
	




	
	
}

TSharedPtr<SHorizontalBox> SLevelToolEditorWidget::CreateLevelItemEvent(const FName LevelName)
{
	return nullptr;
	// TSharedRef<SHorizontalBox>Return_H_Box=SNew(SHorizontalBox);
	// Return_H_Box->AddSlot()
	// [
	// 	SNew(SCheckBox)
	// 	.OnCheckStateChanged(this,&SLevelToolEditorWidget::CheckBoxStateChange)
	// 	//.IsChecked()
	// ];
	// Return_H_Box->AddSlot()
	// [
	// 	SNew(STextBlock)
	// 	.Text(LevelName)
	// ];
	
	// SNew(SCheckBox)
	// .OnCheckStateChanged(this, &SPackageReportDialog::CheckBoxStateChanged, TreeItem, OwnerTable)
	// .IsChecked(this, &SPackageReportDialog::GetEnabledCheckState, TreeItem)



	
}

//
// TSharedRef<SHorizontalBox> SLevelToolEditorWidget::CreateSelecteItem(FName ItemName)
// {
// 	TSharedRef<SHorizontalBox>Item=SNew(SHorizontalBox);
// 	// Item->AddSlot()
// 	// .HAlign(HAlign_Left)
// 	// [
// 	// 	SNew(STextBlock)
// 	// 	.Text(ItemName)
// 	// ];
// 	// Item->AddSlot()
// 	// .HAlign(HAlign_Left)
// 	// [
// 	// 	SNew(SCheckBox)
// 	// 	.IsChecked(ECheckBoxState::Unchecked)
// 	// 	//.OnCheckStateChanged(this,&SLevelToolEditorWidget::GetCheckState)
// 	// ];
// 	return  Item;
// }

FReply SLevelToolEditorWidget::OnClickScaleLevelButton()const
{
	//调用场景缩放
	ULevelToolEditorLibrary::ScaleScene(ScaleTimes,bScaleChildLevel,ReferenceOriginTime);
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

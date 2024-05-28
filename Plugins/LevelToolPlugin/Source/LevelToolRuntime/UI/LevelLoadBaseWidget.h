// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
#include "LevelLoadBaseWidget.generated.h"

class UButton;



/**
 *  该类用于关卡加载UI的基类类型
 */
UCLASS(Blueprintable,BlueprintType)
class LEVELTOOLRUNTIME_API ULevelLoadBaseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct()override
	{
		Super::NativeConstruct();
	}
	/* 用于加载关卡时显示的背景图片 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LevelLoadUI",meta=(BindWidget))
	TObjectPtr<UImage> Level_Load_Background_Image=nullptr;

	/* 用于加载关卡时显示进度的文本 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "LevelLoadUI", meta = (BindWidget))
	TObjectPtr<UTextBlock> Level_Load_Progress_Text = nullptr;

	/* 该方法用于设置Level_Load_Progress_Text的内容 */
	UFUNCTION(BlueprintNativeEvent,Category="LevelLoadUI")
	void Update_Level_Load_Progress_Text(const float Percent);
	virtual void Update_Level_Load_Progress_Text_Implementation(const float Percent)
	{
		Level_Load_Progress_Text->SetText(FText::FromString(FString::FromInt(UKismetMathLibrary::FTrunc(Percent*100))+FString("%")));
	}
};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../Component/LevelToolComponent.h"
#include "LevelToolSubsystem.generated.h"

class ULevelLoadBaseWidget;
class ULevelToolArrayData;
/**
 * 
 */
UCLASS()
class LEVELTOOLRUNTIME_API ULevelToolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual bool ShouldCreateSubsystem(UObject* Outer)const override;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	
	void CreateLoadLevelUI(AGameModeBase* GameModeBase,APlayerController* PlayerController);

public:

	//声明用于子系统的委托
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelToolSubsystemDelegate_OneParam_Float,float,Value);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelToolSubsystemDelegate);

	UPROPERTY(BlueprintAssignable)
	FLevelToolSubsystemDelegate_OneParam_Float Load_Level_Progress;
	
	UPROPERTY(BlueprintAssignable)
	FLevelToolSubsystemDelegate Load_Level_End;

	
	
	/* 由子系统创建的关卡加载UI */
	UPROPERTY()
	ULevelLoadBaseWidget* Level_Load_UI;
	
	/* 实现加载功能的ULevelToolComponent组件 */
	UPROPERTY(BlueprintReadOnly,Category="ULevelToolSubsystem")
	ULevelToolComponent* LevelToolComponent;

	/* 该Actor用于绑定挂在一个ULevelToolComponent组件 */
	UPROPERTY()
	ALevelToolCompoentActor* LevelToolCompoentActor;
	
	/* 用于绑定关卡加载进度委托,在子系统内部使用 */
	UFUNCTION()
	void Level_Load_Percent_Internal(const float Percent)const;

	/* 用于绑定关卡加载完毕委托,在子系统内部使用 */
	UFUNCTION()
	void Level_Load_Complete_Internal();
	
};

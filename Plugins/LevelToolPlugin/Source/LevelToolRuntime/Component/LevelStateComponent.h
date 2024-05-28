// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelStateComponent.generated.h"


/* 关卡状态组件,用于记录返回到之间状态所要显示和隐藏的关卡 */
UCLASS(ClassGroup=(LevelToolComponent), meta=(BlueprintSpawnableComponent),Blueprintable,BlueprintType,HideCategories=ActorComponent)
class LEVELTOOLRUNTIME_API ULevelStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULevelStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
#pragma region 记录相当于初始关卡时操作的关卡状态
public:	
	/* 记录相对于最初状态额外显示的关卡 */
	UPROPERTY(BlueprintReadWrite,Category="ULevelStateComponent")
	TArray<TSoftObjectPtr<UWorld>>ShowLevel;

	/* 记录相对于最初状态额外隐藏的关卡 */
	UPROPERTY(BlueprintReadWrite,Category="ULevelStateComponent")
	TArray<TSoftObjectPtr<UWorld>>HiddenLevel;

	/* 获取进入到一个新的状态时需要操作的关卡 */
	UFUNCTION(BlueprintPure,Category="ULevelStateComponent")
	void GetEnterNewStateProcessLevel(
		const TArray<TSoftObjectPtr<UWorld>>&StartWillShowLevel,
		const TArray<TSoftObjectPtr<UWorld>>&StartWilHiddenLevel,
		TArray<TSoftObjectPtr<UWorld>>&FinalWillShowLevel,
		TArray<TSoftObjectPtr<UWorld>>&FinalWilHiddenLevel);
#pragma endregion
	
#pragma region 模块间控制关卡
public:
	/* 当前模块中显示的关卡 */
	UPROPERTY(BlueprintReadWrite,Category="ULevelStateComponent")
	TArray<TSoftObjectPtr<UWorld>>ModuleShowLevel;

	/* 当前模块中隐藏的关卡 */
	UPROPERTY(BlueprintReadWrite,Category="ULevelStateComponent")
	TArray<TSoftObjectPtr<UWorld>>ModuleHiddenLevel;

	/* 从一个模式当另一个模式需要显示和隐藏的关卡 */
	UFUNCTION(BlueprintCallable,Category="ULevelStateComponent")
	void EnterNewModule(
		const TArray<TSoftObjectPtr<UWorld>>&ModuleWillShowLevel,
		const TArray<TSoftObjectPtr<UWorld>>&ModuleWillHiddenLevel,
		TArray<TSoftObjectPtr<UWorld>>&ModuleFinalWillShowLevel,
		TArray<TSoftObjectPtr<UWorld>>&ModuleFinalWilHiddenLevel);

	/* 在当前的模块中添加额外的关卡到关卡控制中 */
	UFUNCTION(BlueprintCallable,Category="ULevelStateComponent")
	void AddModuleLevel(
		const TArray<TSoftObjectPtr<UWorld>>&ModuleWillShowLevel,
		const TArray<TSoftObjectPtr<UWorld>>&ModuleWillHiddenLevel,
		TArray<TSoftObjectPtr<UWorld>>&ModuleFinalWillShowLevel,
		TArray<TSoftObjectPtr<UWorld>>&ModuleFinalWilHiddenLevel);

	
#pragma endregion

#pragma region 模块内各条目控制关卡
public:
	/* 模块中条目显示的关卡 */
	UPROPERTY(BlueprintReadWrite,Category="ULevelStateComponent")
	TArray<TSoftObjectPtr<UWorld>>ItemShowLevel;

	/* 模块条目中隐藏的关卡 */
	UPROPERTY(BlueprintReadWrite,Category="ULevelStateComponent")
	TArray<TSoftObjectPtr<UWorld>>ItemHiddenLevel;

	/* 模块中一个条目到另一个条目需要显示和隐藏的关卡 */
	UFUNCTION(BlueprintCallable,Category="ULevelStateComponent")
	void EnterNewItem(
		const TArray<TSoftObjectPtr<UWorld>>&ItemWillShowLevel,
		const TArray<TSoftObjectPtr<UWorld>>&ItemWilHiddenLevel,
		TArray<TSoftObjectPtr<UWorld>>&ItemFinalWillShowLevel,
		TArray<TSoftObjectPtr<UWorld>>&ItemFinalWilHiddenLevel);
	

#pragma endregion


	
};

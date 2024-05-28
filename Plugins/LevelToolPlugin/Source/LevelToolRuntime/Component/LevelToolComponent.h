// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelToolComponent.generated.h"

/* 声明单个参数FName委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadLevel_One_Param_FName_Delegate,FName,Name);
/* 声明单个参数float委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadLevel_One_Param_Float_Delegate,float,Value);

/* 关卡工具组件,用于进行关卡的加载与卸载 */
UCLASS(ClassGroup=(LevelToolComponent), meta=(BlueprintSpawnableComponent),Blueprintable,BlueprintType,HideCategories=ActorComponent)
class LEVELTOOLRUNTIME_API ULevelToolComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	ULevelToolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
#pragma region 加载/卸载多个流关卡时开始使用的委托
	/* 开始加载流关卡的委托,包含可视和不可视的关卡 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Start|Load")
	FLoadLevel_One_Param_FName_Delegate Start_Load_Level_Delegate;
	
	/* 开始加载可视的流关卡委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Start|Load")
	FLoadLevel_One_Param_FName_Delegate Start_Load_Visible_Level_Delegate;
	
	/* 开始加载不可视的流关卡委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Start|Load")
	FLoadLevel_One_Param_FName_Delegate Start_Load_NoVisible_Level_Delegate;

	/* 开始卸载流关卡的委托,包含可视和不可视的关卡 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Start|UnLoad")
	FLoadLevel_One_Param_FName_Delegate Start_UnLoad_Level_Delegate;
#pragma endregion 

#pragma region 加载/卸载多个流关卡时更新进度的委托
	/* 加载流关卡时更新进度的委托,包含可视和不可视的关卡 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Progress|Load")
	FLoadLevel_One_Param_Float_Delegate Update_Load_Level_Progress_Delegate;
	
	/* 加载可视的流关卡时更新进度的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Progress|Load")
	FLoadLevel_One_Param_Float_Delegate Update_Load_Visible_Level_Progress_Delegate;
	
	/* 加载可视的流关卡时更新进度的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Progress|Load")
	FLoadLevel_One_Param_Float_Delegate Update_Load_NoVisible_Level_Progress_Delegate;
	
	/* 卸载流关卡时更新进度的委托,包含可视和不可视的关卡 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Progress|UnLoad")
	FLoadLevel_One_Param_Float_Delegate Update_UnLoad_Level_Progress_Delegate;
	
#pragma endregion

#pragma region 加载/卸载多个流关卡时结束使用的委托
	/* 加载流关卡完毕时使用的委托,包含可视和不可视的关卡 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Complete|Load")
	FLoadLevel_One_Param_FName_Delegate EndLevelLoadDelegate;
	
	/* 加载可视的流关卡完毕时使用的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Complete|Load")
	FLoadLevel_One_Param_FName_Delegate End_Load_Visible_Level_Delegate;

	/* 加载不可视的流关卡完毕时使用的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Complete|Load")
	FLoadLevel_One_Param_FName_Delegate End_Load_NoVisible_Level_Delegate;
	
	/* 卸载流关卡完毕时使用的委托,包含可视和不可视的关卡 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Multiple|Complete|UnLoad")
	FLoadLevel_One_Param_FName_Delegate End_UnLoad_Level_Delegate;
	
#pragma endregion

#pragma region 加载/卸载单个流关卡开始时和结束使用的委托
	/* 开始加载单个可视的流关卡的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Single|Start|Load")
	FLoadLevel_One_Param_FName_Delegate Start_Load_Single_Visible_Level_Delegate;

	/* 开始加载单个不可视的流关卡的委托 */
    UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Single|Start|Load")
    FLoadLevel_One_Param_FName_Delegate Start_Load_Single_NoVisible_Level_Delegate;
	
	/* 开始卸载单个流关卡的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Single|Start|UnLoad")
	FLoadLevel_One_Param_FName_Delegate Start_UnLoad_Single_Level_Delegate;

	/* 加载单个可视的流关卡完毕时使用的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Single|Complete|Load")
	FLoadLevel_One_Param_FName_Delegate End_Load_Single_Visible_Level_Delegate;

	/* 加载单个不可视的流关卡完毕时使用的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Single|Complete|Load")
	FLoadLevel_One_Param_FName_Delegate End_Load_Single_NoVisible_Level_Delegate;
	
	/* 卸载单个流关卡完毕时使用的委托 */
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Level|Single|Complete|Load")
	FLoadLevel_One_Param_FName_Delegate End_UnLoad_Single_Level_Delegate;
	
#pragma endregion 

#pragma region 关卡加载/卸载通用参数
public:	
	/* 关卡加载/卸载时是否为阻塞模式 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LevelManagerComponent")
	bool bBlockLoad=false;
#pragma endregion

#pragma region 加载多个流关卡使用属性:包含可视与不可视
private:
	/* 用于记录在当次方法中是否已经调用过Start_Load_Level_Delegate委托 */
	bool bTrigger_Start_Load_Mul_Level_Delegate=false;
	
	/* 用于记录当前要加载的可视的关卡索引 */
	uint8 Load_Mul_Visible_Level_Index=255;

	/* 用于记录当前要加载的不可视的关卡索引 */
	uint8 Load_Mul_NoVisible_Level_Index=255;

	/* 用于记录在Load_Mul_Level方法需要加载的可视的流关卡 */
	TArray<TSoftObjectPtr<UWorld>>Load_Mul_Visible_Level_Array;

	/* 用于记录在Load_Mul_Level方法需要加载的不可视的流关卡 */
	TArray<TSoftObjectPtr<UWorld>>Load_Mul_NoVisible_Level_Array;
	
	/* 用于记录加载多个关卡的Name,用于委托输出 */
	FName Load_Mul_Level_Name;
#pragma endregion

#pragma region 加载多个可视流关卡使用属性
private:	
	/* 用于记录在当次方法中是否已经调用过Start_Load_Visible_Level_Delegate委托 */
	bool bTrigger_Start_Load_Mul_Visible_Level_Delegate=false;
	
	/* 用于记录当前要加载的可视的关卡索引 */
	uint8 Onley_Load_Mul_Visible_Level_Index=255;

	/* 用于记录在Load_Mul_Level方法需要加载的可视的流关卡 */
	TArray<TSoftObjectPtr<UWorld>>Only_Load_Mul_Visible_Level_Array;
	
	/* 用于记录加载多个关卡的Name,用于委托输出 */
	FName Only_Load_Mul_Visible_Level_Name;

	
#pragma endregion

#pragma region 加载多个不可视流关卡使用属性
private:	
	/* 用于记录在当次方法中是否已经调用过Start_Load_Visible_Level_Delegate委托 */
	bool bTrigger_Start_Load_Mul_NoVisible_Level_Delegate=false;
	
	/* 用于记录当前要加载的可视的关卡索引 */
	uint8 Only_Load_Mul_NoVisible_Level_Index=255;

	/* 用于记录在Load_Mul_Level方法需要加载的不可视的流关卡 */
	TArray<TSoftObjectPtr<UWorld>>Only_Load_Mul_NoVisible_Level_Array;
	
	/* 用于记录加载多个关卡的Name,用于委托输出 */
	FName Only_Load_Mul_NoVisible_Level_Name;
	
#pragma endregion

#pragma region 卸载多个流关卡使用属性
private:
	/* 用于记录在当次方法中是否已经调用过Start_UnLoad_Level_Delegate委托 */
	bool bTrigger_Start_UnLoad_Mul_Level_Delegate=false;
	
	/* 用于记录当前要卸载的关卡索引 */
	uint8 UnLoad_Mul_Level_Index=255;
	
	/* 用于记录需要卸载的流关卡 */
	TArray<TSoftObjectPtr<UWorld>>UnLoad_Mul_Level_Array;
	
	/* 用于记录加载多个关卡的Name,用于委托输出 */
	FName UnLoad_Mul_Level_Name;

#pragma endregion
	
#pragma region 加/卸载单个流关卡使用属性
private:	
	/* 用于记录加载单个可视关卡的Name,用于委托输出 */
	FName Load_Single_Visible_Level_Name;

	/* 用于记录加载单个不可视关卡的Name,用于委托输出 */
	FName Load_Single_NoVisible_Level_Name;

	/* 用于记录卸载单个关卡的Name,用于委托输出 */
	FName UnLoad_Single_Level_Name;
#pragma endregion


	
#pragma region 多个流关卡
public:	
	/* 加载多个流关卡,包含可视与不可视 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="ULevelToolComponent")
	void Load_Mul_Level(const TArray<TSoftObjectPtr<UWorld>>&LoadVisibleLevels,const TArray<TSoftObjectPtr<UWorld>>&LoadNoVisibleLevels,const FName Name=FName("-1"));
	virtual void Load_Mul_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>&LoadVisibleLevels,const TArray<TSoftObjectPtr<UWorld>>&LoadNoVisibleLevels,const FName Name=FName("-1"));
	
	/* 加载多个可视的流关卡 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="LevelManagerComponent")
	void Load_Mul_Visible_Level(const TArray<TSoftObjectPtr<UWorld>>&WillLoadStreamings,const FName Name=FName("-1"));
	virtual void Load_Mul_Visible_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>&WillLoadStreamings,const FName Name=FName("-1"));
	
	/* 加载多个不可视的流关卡 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="LevelManagerComponent")
	void Load_Mul_NoVisible_Level(const TArray<TSoftObjectPtr<UWorld>>&WillLoadStreamings,const FName Name=FName("-1"));
	virtual void Load_Mul_NoVisible_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>&WillLoadStreamings,const FName Name=FName("-1"));
	
	/* 卸载多个流关卡 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="LevelManagerComponent")
	void UnLoad_Mul_Level(const TArray<TSoftObjectPtr<UWorld>>&WillUnloadStreamings,const FName Name=FName("-1"));
	virtual void UnLoad_Mul_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>&WillUnloadStreamings,const FName Name=FName("-1"));
	
private:
	/* 用于加载多个流关卡的回调方法,仅用于内部 */
	UFUNCTION()
	void Load_Mul_Level_Internal();

	/* 用于加载多个可视的流关卡的回调方法,仅用于内部 */
	UFUNCTION()
	void Load_Mul_Visible_Level_Internal();

	/* 用于加载多个不可视的流关卡的回调方法,仅用于内部 */
    UFUNCTION()
    void Load_Mul_NoVisible_Level_Internal();

	/* 用于加载多个不可视的流关卡的回调方法,仅用于内部 */
	UFUNCTION()
	void UnLoad_Mul_Level_Internal();

#pragma endregion 

#pragma region 单个流关卡
public:	
	/* 加载一个需要显示的流关卡 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="LevelManagerComponent")
	void Load_Single_Visible_Level(const TSoftObjectPtr<UWorld>&WillLoadStreamings,const FName Name=FName("-1"));
	virtual void Load_Single_Visible_Level_Implementation(const TSoftObjectPtr<UWorld>&WillLoadStreamings,const FName Name=FName("-1"));
	
	/* 加载一个不需要显示的流关卡 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="LevelManagerComponent")
	void Load_Single_NoVisible_Level(const TSoftObjectPtr<UWorld>&WillLoadStreamings,const FName Name=FName("-1"));
	virtual void Load_Single_NoVisible_Level_Implementation(const TSoftObjectPtr<UWorld>&WillLoadStreamings,const FName Name=FName("-1"));
	
	/* 卸载一个流关卡 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="LevelManagerComponent")
	void UnLoad_Single_Level(const TSoftObjectPtr<UWorld>&WillUnloadStreaming,const FName Name=FName("-1"));
	virtual void UnLoad_Single_Level_Implementation(const TSoftObjectPtr<UWorld>&WillUnloadStreaming,const FName Name=FName("-1"));
	
private:
	/* 用于加载一个需要显示的流关卡的回调方法,仅用于内部 */
	UFUNCTION()
	void Load_Single_Visible_Level_Internal();

	/* 用于加载一个不需要显示的流关卡的回调方法,仅用于内部 */
	UFUNCTION()
	void Load_Single_NoVisible_Level_Internal();

	/* 用于卸载一个流关卡的回调方法,仅用于内部 */
    UFUNCTION()
    void UnLoad_Single_Level_Internal();
#pragma endregion 

private:
#pragma region 辅助函数
	/* 获取一个新的UUID值 */
	FORCEINLINE int32 GetNewUUID() const;

#pragma endregion
};


/* 该Actor用于包装ULevelToolComponent组件 */
UCLASS()
class LEVELTOOLRUNTIME_API ALevelToolCompoentActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelToolCompoentActor()
	{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = false;
		LevelToolComponent=CreateDefaultSubobject<ULevelToolComponent>(TEXT("LevelToolComponent"));
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override
	{
		Super::BeginPlay();
	}

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override
	{
		Super::Tick(DeltaTime);
	}

	UPROPERTY(BlueprintReadWrite,Category="ALevelToolCompoentActor")
	ULevelToolComponent* LevelToolComponent;
};
















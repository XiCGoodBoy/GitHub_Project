// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelToolComponent.h"

#include "LevelToolRuntime.h"
#include "Kismet/GameplayStatics.h"


//DEFINE_LOG_CATEGORY(FLevelToolRuntimeLog);

// Sets default values for this component's properties
ULevelToolComponent::ULevelToolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULevelToolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void ULevelToolComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}





#pragma region 多个流关卡

void ULevelToolComponent::Load_Mul_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>&LoadVisibleLevels,const TArray<TSoftObjectPtr<UWorld>>&LoadNoVisibleLevels,const FName Name)
{
	//检查名称是否为空,不为空可能表示前一个任务还未完成
	if (!Load_Mul_Level_Name.IsNone()) return;

	//检查要加载的关卡总数量是否为0
	if ((LoadVisibleLevels.Num()+LoadNoVisibleLevels.Num())==0) return;

	//更新一下名称,用于通知
	Load_Mul_Level_Name=Name;

	//将其索引重置为0
	Load_Mul_Visible_Level_Index=0;
	Load_Mul_NoVisible_Level_Index=0;
	
	//拷贝要加载的关卡内容
	Load_Mul_Visible_Level_Array=LoadVisibleLevels;
	Load_Mul_NoVisible_Level_Array=LoadNoVisibleLevels;
	
	//执行内部方法
	Load_Mul_Level_Internal();
}

void ULevelToolComponent::Load_Mul_Visible_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>& WillLoadStreamings,const FName Name)
{
	//检查名称是否为空,不为空可能表示前一个任务还未完成
	if (!Only_Load_Mul_Visible_Level_Name.IsNone()) return;
	
	//更新一下名称,用于通知
	Only_Load_Mul_Visible_Level_Name=Name;

	//初始化索引
	Onley_Load_Mul_Visible_Level_Index=0;

	//拷贝要加载的关卡内容
	Only_Load_Mul_Visible_Level_Array=WillLoadStreamings;

	//执行内部方法
	Load_Mul_Visible_Level_Internal();
}

void ULevelToolComponent::Load_Mul_NoVisible_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>& WillLoadStreamings,const FName Name)
{
	//检查名称是否为空,不为空可能表示前一个任务还未完成
	if (!Only_Load_Mul_NoVisible_Level_Name.IsNone()) return;
	
	//更新一下名称,用于通知
	Only_Load_Mul_NoVisible_Level_Name=Name;

	//初始化索引
	Only_Load_Mul_NoVisible_Level_Index=0;

	//拷贝要加载的关卡内容
	Only_Load_Mul_NoVisible_Level_Array=WillLoadStreamings;

	//执行内部方法
	Load_Mul_NoVisible_Level_Internal();
}

void ULevelToolComponent::UnLoad_Mul_Level_Implementation(const TArray<TSoftObjectPtr<UWorld>>& WillUnloadStreamings,const FName Name)
{
	//检查名称是否为空,不为空可能表示前一个任务还未完成
	if (!UnLoad_Mul_Level_Name.IsNone()) return;

	//检查要卸载的关卡总数量是否为0
	if (WillUnloadStreamings.Num()==0) return;

	//更新一下名称,用于通知
	UnLoad_Mul_Level_Name=Name;

	//将其索引重置为0
	UnLoad_Mul_Level_Index=0;
	
	//拷贝要加载的关卡内容
	UnLoad_Mul_Level_Array=WillUnloadStreamings;
	
	//执行内部方法
	UnLoad_Mul_Level_Internal();
}

void ULevelToolComponent::Load_Mul_Level_Internal()
{
	//检查是否已经广播过一次开始委托,如果已经调用则调用更新委托
	if (bTrigger_Start_Load_Mul_Level_Delegate)
	{
		UE_LOG(FLevelToolRuntimeLog,Log,TEXT("关卡加载进度:	可视关卡:%d-%d %f,	不可视关卡:%d-%d  %f"),
			Load_Mul_Visible_Level_Index,
			Load_Mul_Visible_Level_Array.Num(),
			(float)Load_Mul_Visible_Level_Index/(float)Load_Mul_Visible_Level_Array.Num(),
			Load_Mul_NoVisible_Level_Index,
			Load_Mul_NoVisible_Level_Array.Num(),
			(float)Load_Mul_NoVisible_Level_Index/(float)Load_Mul_NoVisible_Level_Array.Num()
			);
		//调用更新委托
		Update_Load_Level_Progress_Delegate.Broadcast(((float)(Load_Mul_Visible_Level_Index+Load_Mul_NoVisible_Level_Index))/((float)(Load_Mul_Visible_Level_Array.Num()+Load_Mul_NoVisible_Level_Array.Num())));
	}

	//加载可视关卡
	//先检查当前要加载的可视的关卡索引是否小于数组的元素数量
	if (Load_Mul_Visible_Level_Index<=Load_Mul_Visible_Level_Array.Num()-1)
	{
		//创建一个新的FLatentActionInfo,以便关卡加载完之后执行特定的函数
		FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("Load_Mul_Level_Internal"), this);
		//UUID不能相同,否则将造成崩溃
		LatentForTryLoadLevel.UUID=GetNewUUID();

		//检查是否已经广播过一次开始委托
		if (Load_Mul_Visible_Level_Index==0&&bTrigger_Start_Load_Mul_Level_Delegate==false)
		{
			//广播开始委托
			Start_Load_Level_Delegate.Broadcast(Load_Mul_Level_Name);
			bTrigger_Start_Load_Mul_Level_Delegate=true;
		}
		
		//执行加载
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Load_Mul_Visible_Level_Array[Load_Mul_Visible_Level_Index], true, bBlockLoad, LatentForTryLoadLevel);

		Load_Mul_Visible_Level_Index++;

		//直接返回,之后由LatentAction调用
		return;
	}

	//加载不可视关卡
	//先检查当前要加载的不可视的关卡索引是否小于数组的元素数量
	if (Load_Mul_NoVisible_Level_Index<=Load_Mul_NoVisible_Level_Array.Num()-1)
	{
		//创建一个新的FLatentActionInfo,以便关卡加载完之后执行特定的函数
		FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("Load_Mul_Level_Internal"), this);
		//UUID不能相同,否则将造成崩溃
		LatentForTryLoadLevel.UUID=GetNewUUID();

		//广播通知开始加载多个关卡委托
		if (Load_Mul_NoVisible_Level_Index==0&&bTrigger_Start_Load_Mul_Level_Delegate==false)
		{
			Start_Load_Level_Delegate.Broadcast(Load_Mul_Level_Name);
			bTrigger_Start_Load_Mul_Level_Delegate=true;
		}
		
		//执行加载
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Load_Mul_NoVisible_Level_Array[Load_Mul_NoVisible_Level_Index], false, bBlockLoad, LatentForTryLoadLevel);

		Load_Mul_NoVisible_Level_Index++;

		//直接返回,后续由LatentAction调用
		return;
	}

	//关卡都加载完了,更新状态
	bTrigger_Start_Load_Mul_Level_Delegate=false;
	Load_Mul_Visible_Level_Index=255;
	Load_Mul_NoVisible_Level_Index=255;
	Load_Mul_Visible_Level_Array.Empty();
	Load_Mul_NoVisible_Level_Array.Empty();
	
	//通知关卡都加载完毕
	EndLevelLoadDelegate.Broadcast(Load_Mul_Level_Name);

	Load_Mul_Level_Name=FName();
}

void ULevelToolComponent::Load_Mul_Visible_Level_Internal()
{
	//检查是否已经广播过一次开始委托,如果已经调用则调用更新委托
    if (bTrigger_Start_Load_Mul_Visible_Level_Delegate)
    {
    	//调用更新委托
    	Update_Load_Visible_Level_Progress_Delegate.Broadcast(((float)(Onley_Load_Mul_Visible_Level_Index))/((float)(Only_Load_Mul_Visible_Level_Array.Num())));
    }
    
    //加载可视关卡
    //先检查当前要加载的可视的关卡索引是否小于数组的元素数量
    if (Onley_Load_Mul_Visible_Level_Index<=Only_Load_Mul_Visible_Level_Array.Num()-1)
    {
    	//创建一个新的FLatentActionInfo,以便关卡加载完之后执行特定的函数
    	FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("Load_Mul_Visible_Level_Internal"), this);
    	//UUID不能相同,否则将造成崩溃
    	LatentForTryLoadLevel.UUID=GetNewUUID();
    
    	//检查是否已经广播过一次开始委托
    	if (Onley_Load_Mul_Visible_Level_Index==0&&bTrigger_Start_Load_Mul_Visible_Level_Delegate==false)
    	{
    		//广播开始委托
    		Start_Load_Visible_Level_Delegate.Broadcast(Only_Load_Mul_Visible_Level_Name);
    		bTrigger_Start_Load_Mul_Visible_Level_Delegate=true;
    	}
    	
    	//执行加载
    	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Load_Mul_Visible_Level_Array[Load_Mul_Visible_Level_Index], true, bBlockLoad, LatentForTryLoadLevel);
    
    	Onley_Load_Mul_Visible_Level_Index++;
    
    	//直接返回,之后由LatentAction调用
    	return;
    }
    
    //关卡都加载完了,更新状态
    bTrigger_Start_Load_Mul_Visible_Level_Delegate=false;
    Onley_Load_Mul_Visible_Level_Index=255;
    Only_Load_Mul_Visible_Level_Array.Empty();
    
    //通知关卡都加载完毕
    End_Load_Visible_Level_Delegate.Broadcast(Only_Load_Mul_Visible_Level_Name);
    
    Only_Load_Mul_Visible_Level_Name=FName();
}

void ULevelToolComponent::Load_Mul_NoVisible_Level_Internal()
{
	//检查是否已经广播过一次开始委托,如果已经调用则调用更新委托
	if (bTrigger_Start_Load_Mul_NoVisible_Level_Delegate)
	{
		//调用更新委托
		Update_Load_NoVisible_Level_Progress_Delegate.Broadcast(((float)(Only_Load_Mul_NoVisible_Level_Index))/((float)(Only_Load_Mul_NoVisible_Level_Array.Num())));
	}
    
	//加载可视关卡
	//先检查当前要加载的可视的关卡索引是否小于数组的元素数量
	if (Only_Load_Mul_NoVisible_Level_Index<=Only_Load_Mul_NoVisible_Level_Array.Num()-1)
	{
		//创建一个新的FLatentActionInfo,以便关卡加载完之后执行特定的函数
		FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("Load_Mul_NoVisible_Level_Internal"), this);
		//UUID不能相同,否则将造成崩溃
		LatentForTryLoadLevel.UUID=GetNewUUID();
    
		//检查是否已经广播过一次开始委托
		if (Only_Load_Mul_NoVisible_Level_Index==0&&bTrigger_Start_Load_Mul_NoVisible_Level_Delegate==false)
		{
			//广播开始委托
			Start_Load_NoVisible_Level_Delegate.Broadcast(Only_Load_Mul_NoVisible_Level_Name);
			bTrigger_Start_Load_Mul_NoVisible_Level_Delegate=true;
		}
    	
		//执行加载
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Only_Load_Mul_NoVisible_Level_Array[Only_Load_Mul_NoVisible_Level_Index], false, bBlockLoad, LatentForTryLoadLevel);
    
		Only_Load_Mul_NoVisible_Level_Index++;
    
		//直接返回,之后由LatentAction调用
		return;
	}
    
	//关卡都加载完了,更新状态
	bTrigger_Start_Load_Mul_NoVisible_Level_Delegate=false;
	Only_Load_Mul_NoVisible_Level_Index=255;
	Only_Load_Mul_NoVisible_Level_Array.Empty();
    
	//通知关卡都加载完毕
	End_Load_NoVisible_Level_Delegate.Broadcast(Only_Load_Mul_NoVisible_Level_Name);
    
	Only_Load_Mul_NoVisible_Level_Name=FName();
}

void ULevelToolComponent::UnLoad_Mul_Level_Internal()
{
	//检查是否已经广播过一次开始委托,如果已经调用则调用更新委托
	if (bTrigger_Start_UnLoad_Mul_Level_Delegate)
	{
		//调用更新委托
		Update_UnLoad_Level_Progress_Delegate.Broadcast((float)(UnLoad_Mul_Level_Index)/(float)(UnLoad_Mul_Level_Array.Num()));
	}

	//卸载可视关卡
	//先检查当前要卸载的关卡索引是否小于数组的元素数量
	if (UnLoad_Mul_Level_Index<=UnLoad_Mul_Level_Array.Num()-1)
	{
		//创建一个新的FLatentActionInfo,以便关卡加载完之后执行特定的函数
		FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("UnLoad_Mul_Level_Internal"), this);
		//UUID不能相同,否则将造成崩溃
		LatentForTryLoadLevel.UUID=GetNewUUID();

		//检查是否已经广播过一次开始委托
		if (UnLoad_Mul_Level_Index==0&&bTrigger_Start_UnLoad_Mul_Level_Delegate==false)
		{
			//广播开始委托
			Start_UnLoad_Level_Delegate.Broadcast(UnLoad_Mul_Level_Name);
			bTrigger_Start_UnLoad_Mul_Level_Delegate=true;
		}
		
		//执行卸载
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, UnLoad_Mul_Level_Array[UnLoad_Mul_Level_Index],LatentForTryLoadLevel,bBlockLoad);

		UnLoad_Mul_Level_Index++;

		//直接返回,之后由LatentAction调用
		return;
	}

	//关卡都卸载完了,更新状态
    bTrigger_Start_UnLoad_Mul_Level_Delegate=false;
    UnLoad_Mul_Level_Index=255;
    UnLoad_Mul_Level_Array.Empty();
    
    //通知关卡都加载完毕
    End_UnLoad_Level_Delegate.Broadcast(UnLoad_Mul_Level_Name);
    
    UnLoad_Mul_Level_Name=FName();
}

#pragma endregion 

#pragma region 单个流关卡
void ULevelToolComponent::Load_Single_Visible_Level_Implementation(const TSoftObjectPtr<UWorld> &WillLoadStreamings,const FName Name)
{
	//检查名称是否为空,不为空可能表示前一个任务还未完成
	if (!Load_Single_Visible_Level_Name.IsNone()) return;

	//更新一下名称,用于通知
	Load_Single_Visible_Level_Name=Name;

	//创建一个新的FLatentActionInfo,以关卡加载完之后执行
	FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("Load_Single_Visible_Level_Internal"), this);
	//UUID不能相同,否则将造成崩溃
	LatentForTryLoadLevel.UUID=GetNewUUID();

	//通知开始加载单个可视关卡
	Start_Load_Single_Visible_Level_Delegate.Broadcast(Load_Single_Visible_Level_Name);
	
	//执行加载
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, WillLoadStreamings, true, bBlockLoad, LatentForTryLoadLevel);
}

void ULevelToolComponent::Load_Single_NoVisible_Level_Implementation(const TSoftObjectPtr<UWorld>& WillLoadStreamings,const FName Name)
{
	//检查名称是否为空,不为空可能表示前一个任务还未完成
	if (!Load_Single_NoVisible_Level_Name.IsNone()) return;

	//更新一下名称,用于通知
	Load_Single_NoVisible_Level_Name=Name;

	//创建一个新的FLatentActionInfo,以关卡加载完之后执行
	FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("Load_Single_NoVisible_Level_Internal"), this);
	//UUID不能相同,否则将造成崩溃
	LatentForTryLoadLevel.UUID=GetNewUUID();

	//通知开始加载单个不可视关卡
	Start_Load_Single_NoVisible_Level_Delegate.Broadcast(Load_Single_NoVisible_Level_Name);
	
	//执行加载
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, WillLoadStreamings, false, bBlockLoad, LatentForTryLoadLevel);
	
}

void ULevelToolComponent::UnLoad_Single_Level_Implementation(const TSoftObjectPtr<UWorld> &WillUnloadStreaming,const FName Name)
{
	//检查名称是否为空,不为空可能表示前一个任务还未完成
	if (!UnLoad_Single_Level_Name.IsNone()) return;

	//更新一下名称,用于通知
	UnLoad_Single_Level_Name=Name;

	//创建一个新的FLatentActionInfo,以关卡加载完之后执行
	FLatentActionInfo LatentForTryLoadLevel = FLatentActionInfo(1, 1,TEXT("UnLoad_Single_Level_Internal"), this);
	//UUID不能相同,否则将造成崩溃
	LatentForTryLoadLevel.UUID=GetNewUUID();

	//通知开始卸载单个关卡
	Start_UnLoad_Single_Level_Delegate.Broadcast(UnLoad_Single_Level_Name);
	
	//执行卸载
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, WillUnloadStreaming,LatentForTryLoadLevel,bBlockLoad);
}

void ULevelToolComponent::Load_Single_Visible_Level_Internal()
{
	//检查Load_Single_Visible_Level_Name是否为空,为空表示有问题
	check(!Load_Single_Visible_Level_Name.IsNone())

	//通知结束加载单个可视关卡
	End_Load_Single_Visible_Level_Delegate.Broadcast(Load_Single_Visible_Level_Name);

	//将值置为空
	Load_Single_Visible_Level_Name=FName();
}

void ULevelToolComponent::Load_Single_NoVisible_Level_Internal()
{
	//检查是否为空,为空表示有问题
	check(!Load_Single_NoVisible_Level_Name.IsNone())

	//通知结束加载单个不可视关卡
	End_Load_Single_NoVisible_Level_Delegate.Broadcast(Load_Single_NoVisible_Level_Name);

	//将值置为空
	Load_Single_NoVisible_Level_Name=FName();
}

void ULevelToolComponent::UnLoad_Single_Level_Internal()
{
	//检查是否为空,为空表示有问题
	check(!UnLoad_Single_Level_Name.IsNone())

	//通知结束卸载单个关卡
	End_UnLoad_Single_Level_Delegate.Broadcast(UnLoad_Single_Level_Name);

	//将值置为空
	UnLoad_Single_Level_Name = FName();
}


#pragma endregion

#pragma region 辅助函数

int32 ULevelToolComponent::GetNewUUID() const
{
	return  FGuid::NewGuid().A;
}


#pragma endregion
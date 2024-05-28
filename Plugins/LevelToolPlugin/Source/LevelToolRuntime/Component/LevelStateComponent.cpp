// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStateComponent.h"


// Sets default values for this component's properties
ULevelStateComponent::ULevelStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULevelStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULevelStateComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma region 记录相当于初始关卡时操作的关卡状态
void ULevelStateComponent::GetEnterNewStateProcessLevel(
	const TArray<TSoftObjectPtr<UWorld>>& StartWillShowLevel,
	const TArray<TSoftObjectPtr<UWorld>>& StartWilHiddenLevel,
	TArray<TSoftObjectPtr<UWorld>>& FinalWillShowLevel,
	TArray<TSoftObjectPtr<UWorld>>& FinalWilHiddenLevel)
{
	//声明两个数组
	TArray<TSoftObjectPtr<UWorld>>TemShowLevel=HiddenLevel,TemHiddenLevel=ShowLevel;

	//for循环检查还要显示的Level
	for (TSoftObjectPtr<UWorld>TemLevel :StartWillShowLevel)
	{
		//检查关卡对象是否有效
		if (!(TemLevel->IsValidLowLevelFast())) continue;

		//确保已经显示的关卡没有要再执行显示的关卡
		if (TemShowLevel.Contains(TemLevel))
		{
			TemShowLevel.Remove(TemLevel);
		}
		else
		{
			TemShowLevel.Add(TemLevel);
		}

		//确保要隐藏的关卡中没有要显示的关卡
		if (TemHiddenLevel.Contains(TemLevel)) TemHiddenLevel.Remove(TemLevel);
	}

	//for循环检查还要隐藏的Level
	for (TSoftObjectPtr<UWorld>TemLevel :StartWilHiddenLevel)
	{
		//检查关卡对象是否有效
		if (!(TemLevel.Get()->IsValidLowLevelFast())) continue;

		//确保已经隐藏的关卡没有要再执行隐藏的关卡
		if (TemHiddenLevel.Contains(TemLevel))
		{
			TemHiddenLevel.Remove(TemLevel);
		}
		else
		{
			TemHiddenLevel.Add(TemLevel);
		}

		//确保要显示的关卡中没有要隐藏的关卡
		if (TemShowLevel.Contains(TemLevel)) TemShowLevel.Remove(TemLevel);
	}

	//最终需要操作显示和隐藏的关卡
	FinalWillShowLevel=TemShowLevel;
	FinalWilHiddenLevel=TemHiddenLevel;
}
#pragma endregion

#pragma region 模块间控制关卡
void ULevelStateComponent::EnterNewModule(
	const TArray<TSoftObjectPtr<UWorld>>& ModuleWillShowLevel,
	const TArray<TSoftObjectPtr<UWorld>>& ModuleWillHiddenLevel,
	TArray<TSoftObjectPtr<UWorld>>& ModuleFinalWillShowLevel,
	TArray<TSoftObjectPtr<UWorld>>& ModuleFinalWilHiddenLevel)
{
	//模块间切换:恢复上一个模块条目显示和隐藏的内容 + 上一个模块显示和隐藏的内容 ,显示和隐藏当前模块的内容.
	//	1.将前一个模块显示的关卡恢复隐藏,将隐藏的关卡恢复显示
	//								|
	//	2.将前一个模块条目下显示的关卡恢复隐藏,将隐藏的关卡恢复显示
	//								|
	//	3.检查新模块需要显示的关卡:是否已经在前一个模块中显示,不需要再进行显示
	//								|
	//	4.检查新模块需要显示的关卡:不应该在处于需要恢复隐藏的关卡数组中
	//								|
	//	5.检查新模块需要隐藏的关卡:是否已经在前一个条目中隐藏,不需要再进行隐藏
	//								|
	//	6.检查新模块需要隐藏的关卡:不应该在处于需要恢复显示的关卡数组中
	//								|
	//	7.筛选之后前一个模块需要显示的关卡 + 新模块需要显示
	//								|
	//	8.筛选之后前一个模块需要隐藏的关卡 + 新模块需要隐藏

	///////////////////////////////////////////////////////////////////
	//筛选掉模块和模块下操作的同名关卡:开始
	///////////////////////////////////////////////////////////////////

	//先确定当前模块条目下额外隐藏的关卡是否与模块的关卡相同
	for (TSoftObjectPtr<UWorld>TemShowLevel :ModuleWillShowLevel)
	{
		//检查该关卡是否已经在模块中进行隐藏处理
		if (ModuleHiddenLevel.Contains(TemShowLevel))
		{
			//就先将模块中的对应关卡移除掉
			ModuleHiddenLevel.Remove(TemShowLevel);
		}

		//检查该关卡是否已经在模块中进行显示处理
		if (ModuleShowLevel.Contains(TemShowLevel))
		{
			//就先将模块中的对应关卡移除掉
			ModuleShowLevel.Remove(TemShowLevel);
		}
		//此时模块条目下的隐藏关卡数组与模块的关卡无重复
	}

	//先确定当前模块条目下额外显示的关卡是否与模块的关卡相同
	for (TSoftObjectPtr<UWorld>TemHiddenLevel :ItemShowLevel)
	{
		//检查该关卡是否已经在模块中进行隐藏处理
		if (ModuleHiddenLevel.Contains(TemHiddenLevel))
		{
			//就先将模块中的对应关卡移除掉,以模块下的关卡状态为准
			ModuleHiddenLevel.Remove(TemHiddenLevel);
		}
	
		//检查该关卡是否已经在模块中进行显示处理
		if (ModuleShowLevel.Contains(TemHiddenLevel))
		{
			//就先将模块中的对应关卡移除掉
			ModuleShowLevel.Remove(TemHiddenLevel);
		}
		//此时模块条目下的显示的关卡数组与模块的关卡无重复
	}

	///////////////////////////////////////////////////////////////////
	//筛选掉模块和模块下操作的同名关卡:结束
	///////////////////////////////////////////////////////////////////

	//恢复前一个模块的所有显示和隐藏关卡
	ItemHiddenLevel.Append(ModuleHiddenLevel);
	TArray<TSoftObjectPtr<UWorld>>RecoverShowLevel=ItemHiddenLevel;
	
	ItemShowLevel.Append(ModuleShowLevel);
	TArray<TSoftObjectPtr<UWorld>>RecoverHiddenLevel=ItemShowLevel;
	
	
	//检查需要恢复的关卡与在新模块中显示的关卡有没有相同的关卡
	for (TSoftObjectPtr<UWorld>TemShowLevel :ModuleWillShowLevel)
	{
		//检查准备恢复显示的关卡 是否 包含
		if (RecoverShowLevel.Contains(TemShowLevel))
		{
			//对应关卡移除掉,后续合并再加进来
		}
		else
		{
			RecoverShowLevel.Add(TemShowLevel);
		}

		//检查准备恢复隐藏的关卡 是否 包含
		if (RecoverHiddenLevel.Contains(TemShowLevel))
		{
			//在新模块中需要显示则不需要进行隐藏处理
			RecoverHiddenLevel.Remove(TemShowLevel);
		}
	}

	//检查需要恢复的关卡与在新模块中显示的关卡有没有相同的关卡
	for (TSoftObjectPtr<UWorld>TemHiddenLevel :ModuleWillHiddenLevel)
	{
		//检查准备恢复显示的关卡 是否 包含
		if (RecoverShowLevel.Contains(TemHiddenLevel))
		{
			//在新模块中需要隐藏则不需要进行显示处理
			RecoverShowLevel.Remove(TemHiddenLevel);
		}

		//检查准备恢复隐藏的关卡 是否 包含
		if (RecoverHiddenLevel.Contains(TemHiddenLevel))
		{
			//在新模块中需要显示则不需要进行隐藏处理
			RecoverHiddenLevel.Remove(TemHiddenLevel);
		}
		else
		{
			//不在数组中,需要进行隐藏处理
			RecoverHiddenLevel.Add(TemHiddenLevel);
		}
	}
	
	
	//最终需要显示和隐藏的关卡
	ModuleFinalWillShowLevel=RecoverShowLevel;
	ModuleFinalWilHiddenLevel=RecoverHiddenLevel;
	ItemShowLevel.Empty();
	ItemHiddenLevel.Empty();
	ModuleShowLevel=ModuleWillShowLevel;
	ModuleHiddenLevel=ModuleWillHiddenLevel;
}

void ULevelStateComponent::AddModuleLevel(
	const TArray<TSoftObjectPtr<UWorld>>& ModuleWillShowLevel,
	const TArray<TSoftObjectPtr<UWorld>>& ModuleWillHiddenLevel,
	TArray<TSoftObjectPtr<UWorld>>& ModuleFinalWillShowLevel,
	TArray<TSoftObjectPtr<UWorld>>& ModuleFinalWilHiddenLevel)
{
	TArray<TSoftObjectPtr<UWorld>>FinalWillShowLevel,FinalWilHiddenLevel;
	
	//将额外显示的关卡添加到数组中
	for (TSoftObjectPtr<UWorld>TemShowLevel :ModuleWillShowLevel)
	{
		//检查要显示的关卡是否在模块初始时就已经显示
		if (ModuleShowLevel.Contains(TemShowLevel))
		{
			//已经在模块中显示了,不需要再进行显示操作

			//确保隐藏的关卡中没有该项,这一步可能有点多余
			if (ModuleHiddenLevel.Contains(TemShowLevel))
			{
				ModuleHiddenLevel.Remove(TemShowLevel);
			}
			
		}
		else
		{
			//检查要显示的关卡是否在模块初始时就隐藏
			if (ModuleHiddenLevel.Contains(TemShowLevel))
			{
				//从隐藏控制数组中移除
				ModuleHiddenLevel.Remove(TemShowLevel);

				//将显示的关卡加入显示控制数组中
				ModuleShowLevel.AddUnique(TemShowLevel);
				
				//未在模块中显示,需要进行显示操作
				FinalWillShowLevel.AddUnique(TemShowLevel);
			}
			else
			{
				//未在模块中显示,需要进行显示操作
				FinalWillShowLevel.AddUnique(TemShowLevel);
			}
			
		}
		
	}

	//将额外隐藏的关卡添加到数组中
	for (TSoftObjectPtr<UWorld>TemHiddenLevel :ModuleWillHiddenLevel)
	{
		//检查要隐藏的关卡是否在模块初始时就已经显示
		if (ModuleShowLevel.Contains(TemHiddenLevel))
		{
			//将在模块初始时就已经显示的关卡从隐藏状态数组中移除,加入到显示状态控制数组
			ModuleHiddenLevel.Remove(TemHiddenLevel);
			ModuleShowLevel.AddUnique(TemHiddenLevel);
			FinalWilHiddenLevel.AddUnique(TemHiddenLevel);
		}
		else
		{
			//检查要隐藏的关卡是否在模块初始时就隐藏
			if (ModuleHiddenLevel.Contains(TemHiddenLevel))
			{
				//已经处于隐藏状态,不需要再进行操作
			}
			else
			{
				//未在模块中隐藏,需要进行隐藏操作
				FinalWilHiddenLevel.AddUnique(TemHiddenLevel);
			}
			
		}
	}
	
	ModuleFinalWillShowLevel=FinalWillShowLevel;
	ModuleFinalWilHiddenLevel=ModuleWillHiddenLevel;
	
}
#pragma endregion

#pragma region 模块内各条目控制关卡
void ULevelStateComponent::EnterNewItem(
	const TArray<TSoftObjectPtr<UWorld>>& ItemWillShowLevel,
	const TArray<TSoftObjectPtr<UWorld>>& ItemWilHiddenLevel,
	TArray<TSoftObjectPtr<UWorld>>& ItemFinalWillShowLevel,
	TArray<TSoftObjectPtr<UWorld>>& ItemFinalWilHiddenLevel)
{
	//模块条目间切换、恢复上一个条目显示和隐藏的内容,显示和隐藏当前条目的内容,
	//								|
	//	1.将前一个条目下显示的关卡恢复隐藏,将隐藏的关卡恢复显示（旧条目的关卡可能与新条目的关卡相同）
	//								|
	//	2.检查新条目需要显示的关卡:是否已经在前一个条目中显示,不需要再进行显示
	//								|
	//	3.检查新条目需要显示的关卡:不应该在处于需要恢复隐藏的关卡数组中
	//								|
	//	4.检查新条目需要隐藏的关卡:是否已经在前一个条目中隐藏,不需要再进行隐藏
	//								|
	//	5.检查新条目需要隐藏的关卡:不应该在处于需要恢复显示的关卡数组中
	//								|
	//	6.筛选之后前一个条目需要显示的关卡 + 新条目需要显示
	//								|
	//	7.筛选之后前一个条目需要隐藏的关卡 + 新条目需要隐藏
	
	//2.检查新条目需要显示的关卡:在前一个条目中显示,不需要再进行显示处理
	//3.检查新条目需要显示的关卡:不应该在处于需要恢复隐藏的关卡数组中
	//6.筛选之后前一个条目需要显示的关卡 + 新条目需要显示
	for (TSoftObjectPtr<UWorld>TemShowLevel :ItemWillShowLevel)
	{
		//检查关卡对象是否有效
		if (!(TemShowLevel->IsValidLowLevelFast())) continue;

		//检查已经隐藏准备显示的关卡数组:是否包含需要显示的关卡
		if (ItemHiddenLevel.Contains(TemShowLevel))
		{
			//已经隐藏准备显示的关卡数组:已经包含,不需要重复添加一个需要显示的关卡
		}
		else
		{
			//检查已经显示准备隐藏的关卡数组是否包含需要显示的关卡
			if (ItemShowLevel.Contains(TemShowLevel))
			{
				//在前条目中已经显示的关卡不需要恢复隐藏,因为在新条目中仍然需要显示
				ItemShowLevel.Remove(TemShowLevel);
			}
			else
			{
				//已经隐藏准备显示的关卡数组:不包含,添加一个需要显示的关卡
				ItemHiddenLevel.Add(TemShowLevel);
			}
			
		}
	}


	//4.检查新条目需要隐藏的关卡:是否已经在前一个条目中隐藏,不需要再进行隐藏
	//5.检查新条目需要隐藏的关卡:不应该在处于需要恢复显示的关卡数组中
	//7.筛选之后前一个条目需要隐藏的关卡 + 新条目需要隐藏
	for (TSoftObjectPtr<UWorld>TemHiddenLevel :ItemWilHiddenLevel)
	{
		//检查关卡对象是否有效
		if (!(TemHiddenLevel.Get()->IsValidLowLevelFast())) continue;

		//检查已经显示准备隐藏的关卡数组:是否包含需要隐藏的关卡
		if (ItemShowLevel.Contains(TemHiddenLevel))
		{
			//已经显示准备隐藏的关卡数组:已经包含,不需要重复添加一个需要隐藏的关卡
		}
		else
		{
			//检查已经隐藏准备显示的关卡数组是否包含需要隐藏的关卡
			if (ItemHiddenLevel.Contains(TemHiddenLevel))
			{
				ItemHiddenLevel.Remove(TemHiddenLevel);
			}
			else
			{
				//已经显示准备隐藏的关卡数组:不包含,添加一个需要隐藏的关卡
				ItemShowLevel.Add(TemHiddenLevel);
			}
		}
	}
	
	//最终需要显示和隐藏的关卡
	ItemFinalWillShowLevel=ItemHiddenLevel;
	ItemFinalWilHiddenLevel=ItemShowLevel;
	ItemShowLevel=ItemWillShowLevel;
	ItemHiddenLevel=ItemWilHiddenLevel;
}



#pragma endregion




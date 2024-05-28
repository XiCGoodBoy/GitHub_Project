// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HelperStructType.generated.h"

/* 这个结构体用于记录关卡数组 */
USTRUCT(BlueprintType,BlueprintType)
struct FLevelArrayHelperStruct
{
	GENERATED_BODY()
public:
	/* 存储关卡的数组 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FLevelArrayHelperStruct")
	TArray<TSoftObjectPtr<UWorld>>LevelArray;
};



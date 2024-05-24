// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileHelperBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class IVWEBSOCKET_API UFileHelperBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**获取Actor配置的保存路径*/
	UFUNCTION(BlueprintPure, Category="FileHelper")
	static FString GetActorJsonConfigDir();
};

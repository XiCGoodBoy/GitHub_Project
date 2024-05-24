// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class IVWEBSOCKET_API FIVJsonConfig
{
private:
	TFuture<void> SaveFuture;
	FSimpleDelegate OnConfigChange;
	TSharedPtr<FIVJsonConfig> ParentConfig;
	TSharedPtr<FJsonObject> OverrideObject;
	TSharedPtr<FJsonObject> MergedObject;

public:
	FIVJsonConfig();

	TSharedPtr<FJsonObject> GetRootObject();

	bool SaveToString(FString& OutResult);
};

// class IVWEBSOCKET_API FIVJsonPath
// {
// public:
// 	struct FIVPart
// 	{
// 		FString Name;
// 		int32 Index = INDEX_NONE;
// 	};
// };

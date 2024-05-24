// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IVJsonConfig.h"


class IVWEBSOCKET_API FIVConfig
{
	// DECLARE_EVENT_OneParam(FIVConfig, FOnIVConfigDirtied, const FIVConfig&);

private:
	bool Dirty = false;
	TSharedPtr<FIVConfig> ParentConfig;
	TSharedPtr<FIVJsonConfig> JsonConfig;
	// FOnIVConfigDirtied IVConfigDirtiedEvent;

public:
	FIVConfig();

	bool IsValid() const;

	bool LoadFromString(FStringView Content);


	bool SaveToString(FString& OutResult);

	// UStruct & UObject
	void SetRootUObject(const UClass* Class, const UObject* Instance);

	bool TryGetRootUObject(const UClass* Class, UObject* OutValue);

public:
	static TSharedPtr<FJsonObject> WriteUObject(const UClass* Class, const UObject* Instance);
};

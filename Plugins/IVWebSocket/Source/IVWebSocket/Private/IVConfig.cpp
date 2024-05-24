// Fill out your copyright notice in the Description page of Project Settings.


#include "IVConfig.h"

#include "JsonObjectConverter.h"

bool FIVConfig::IsValid() const
{
	return JsonConfig.IsValid() && JsonConfig.IsValid();
}

bool FIVConfig::LoadFromString(FStringView Content)
{
	JsonConfig = MakeShared<FIVJsonConfig>();
	// if (!JsonConfig->LoadFromString(Content))
	return false;
}

bool FIVConfig::SaveToString(FString& OutResult)
{
	if (IsValid()) return false;

	return JsonConfig->SaveToString(OutResult);
}

void FIVConfig::SetRootUObject(const UClass* Class, const UObject* Instance)
{
	if (!IsValid()) return;

	// TSharedPtr<FJsonObject>JsonObject=write
}

bool FIVConfig::TryGetRootUObject(const UClass* Class, UObject* OutValue)
{
	if (!IsValid()) return false;

	TSharedPtr<FJsonObject> UObjectData = JsonConfig->GetRootObject();
	// read

	return true;
}

TSharedPtr<FJsonObject> FIVConfig::WriteUObject(const UClass* Class, const UObject* Instance)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("$Type"), Class->GetName());

	const UObject* Defaults = Class->GetDefaultObject();

	bool bAnyWritten = false;

	for (TFieldIterator<FProperty> It(Class); It; ++It)
	{
		const FProperty* Property = *It;
		if (!Property->HasAnyPropertyFlags(CPF_Config) || Property->GetName() ==
			TEXT("DefaultUpdateOverlapsMethodDuringLevelStreaming") || Property->GetName() == TEXT(
				"bReplicateUsingRegisteredSubObjectList"))
			continue;

		bAnyWritten = true;

		const void* ValuePtr = Property->ContainerPtrToValuePtr<void>(Instance);
		const void* PropertyDefaultPtr = Property->ContainerPtrToValuePtr<void>(Defaults);

		TSharedPtr<FJsonValue> PropertyValue;
		if (PropertyValue.IsValid())
		{
			// JsonObject->SetField(FJsonObjectConverter::StandardizeCase())
		}
	}

	return JsonObject;
}

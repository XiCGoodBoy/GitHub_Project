// Fill out your copyright notice in the Description page of Project Settings.


#include "IVJsonConfig.h"

FIVJsonConfig::FIVJsonConfig()
{
	OverrideObject = MakeShared<FJsonObject>();
	MergedObject = MakeShared<FJsonObject>();
}

TSharedPtr<FJsonObject> FIVJsonConfig::GetRootObject()
{
	return MergedObject;
}


bool FIVJsonConfig::SaveToString(FString& OutResult)
{
	if (!OverrideObject.IsValid()) return false;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutResult);
	if (!FJsonSerializer::Serialize(OverrideObject.ToSharedRef(), Writer.Get())) return false;

	return true;
}

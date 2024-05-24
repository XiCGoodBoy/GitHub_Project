// Fill out your copyright notice in the Description page of Project Settings.


#include "FileHelperBPLibrary.h"

FString UFileHelperBPLibrary::GetActorJsonConfigDir()
{
	return FPaths::ProjectConfigDir() / "ActorJsonConfig";
}

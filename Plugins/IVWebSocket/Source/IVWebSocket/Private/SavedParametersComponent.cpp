// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedParametersComponent.h"
#include "FileHelperBPLibrary.h"

#include "FileHelperBPLibrary.h"
#include "IVConfig.h"

// Sets default values for this component's properties
USavedParametersComponent::USavedParametersComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITOR
	FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(
		this, &USavedParametersComponent::OnActorEditChangeProperty);
#endif

	if (GetOwner())
	{
		FilePath = UFileHelperBPLibrary::GetActorJsonConfigDir() / GetOwner()->GetName() + ".json";
	}
}

void USavedParametersComponent::PostReinitProperties()
{
	Super::PostReinitProperties();
}

#if WITH_EDITOR
void USavedParametersComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void USavedParametersComponent::OnActorEditChangeProperty(UObject* Actor, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (!GetOwner())
	{
		return;
	}

	if (Actor->GetName() == GetOwner()->GetName())
	{
		if (GetOwner()->GetName().StartsWith("Default__C") || GetOwner()->GetName().EndsWith(TEXT("_C_0"))) return;

		// FIVConfig Config;
		FString Result;
		//Config.SetRootUObject(GetOwner()->GetClass(), GetOwner());
		// if (!Config.SaveToString(Result)) return;

		// FFileHelper::SaveStringToFile(Result, *FilePath);
	}
}
#endif

// Called when the game starts
void USavedParametersComponent::BeginPlay()
{



	

	// Super::BeginPlay();
	//
	// if (!GetOwner()) return;
	//
	// if (HasAnyFlags(RF_ClassDefaultObj ect | RF_Transient)) return;
	//
	// if (GetOwner()->GetName().StartsWith("Default__C") || GetOwner()->GetName().EndsWith(TEXT("_C_0"))) return;
	//
	// FIVConfig Config;
	// FString Contents;
	// if (!FFileHelper::LoadFileToString(Contents, *FilePath)) return;
	//
	// if (!Config.LoadFromString(Contents)) return;
	//
	// Config.TryGetRootUObject(GetOwner()->GetClass(), GetOwner());
}

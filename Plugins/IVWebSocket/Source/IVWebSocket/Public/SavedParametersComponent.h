// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SavedParametersComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IVWEBSOCKET_API USavedParametersComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// 用于保存json路径
	FString FilePath;

public:
	USavedParametersComponent();

	// Begin UObject Interface.
	virtual void PostReinitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void OnActorEditChangeProperty(UObject* Actor, struct FPropertyChangedEvent& PropertyChangedEvent);
#endif
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};

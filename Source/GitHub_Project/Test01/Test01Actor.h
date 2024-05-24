// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Test01Actor.generated.h"

UENUM()
enum class Eabc:uint8
{
	a,
	b,
	c
};

UCLASS()
class GITHUB_PROJECT_API ATest01Actor : public AActor
{
	GENERATED_BODY()

	TFuture<void> SaveFuture;

public:
	// Sets default values for this actor's properties
	ATest01Actor();

	UFUNCTION(BlueprintCallable)
	void Test01Play();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

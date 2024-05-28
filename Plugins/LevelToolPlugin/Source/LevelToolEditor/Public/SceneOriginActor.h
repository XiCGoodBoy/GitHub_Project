// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneOriginActor.generated.h"



//此Actor用与实例化到场景中,用于缩放场景中的模型
UCLASS()
class LEVELTOOLEDITOR_API ASceneOriginActor : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ASceneOriginActor();

	UPROPERTY()
	USceneComponent* ActorRootComponent;

	//广告板
	UPROPERTY()
	UBillboardComponent* BillboardComponent;
	
	//: SpriteTexture(TEXT("/Engine/EditorResources/S_Actor"))
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

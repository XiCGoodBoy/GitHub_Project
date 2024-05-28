// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SceneOriginActor.h"
#include "Components/BillboardComponent.h"


// Sets default values
ASceneOriginActor::ASceneOriginActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建ActorRootComponent组件
	if (!ActorRootComponent)
	{
		ActorRootComponent=CreateDefaultSubobject<USceneComponent>(FName(TEXT("SceneRoot")),false);
		this->SetRootComponent(ActorRootComponent);
	}

	//创建广告板组件
	if (!BillboardComponent)
	{
		 BillboardComponent=CreateDefaultSubobject<UBillboardComponent>(FName(TEXT("Billboard")));
		 if (UTexture2D* Billboard=LoadObject<UTexture2D>(this,TEXT("Texture2D'/Engine/EditorResources/EmptyActor.EmptyActor'")))
		 {
			 BillboardComponent->SetSprite(Billboard);
		 }
		BillboardComponent->AttachToComponent(ActorRootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	}

	
	
	
}

// Called when the game starts or when spawned
void ASceneOriginActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASceneOriginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


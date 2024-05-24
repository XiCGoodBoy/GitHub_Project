// Fill out your copyright notice in the Description page of Project Settings.


#include "Test01Actor.h"


// Sets default values
ATest01Actor::ATest01Actor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATest01Actor::Test01Play()
{
}


int32 LongRunningTask()
{
	FPlatformProcess::Sleep(10.0f);
	return 42;
}

void ATest01Actor::BeginPlay()
{
	// Super::BeginPlay();
	//
	// TPromise<int32> Promise;
	//
	// TFuture<int32> Future = Promise.GetFuture();

	// Async(EAsyncExecution::ThreadPool, [&Promise]()
	// {
	// 	int32 Result = LongRunningTask();
	// 	Promise.SetValue(Result);
	// });
	//
	// int32 Result = Future.Get();
	// UE_LOG(LogTemp, Warning, TEXT("the long running task: %d"), Result);
	
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,FString::Printf(TEXT("%d"),UEnum::LookupEnumName(FName(),TEXT("EABC::c"))));
	for (TObjectIterator<UEnum> It; It; ++It)
	{
		UEnum* Enum = *It;
		if (Enum)
		{
			FString EnumName = Enum->GetName();
			UE_LOG(LogTemp, Log, TEXT("Enum Name: %s"), *EnumName);
		}
	}
}


void ATest01Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Async/AsyncWork.h"
#include "Multithreaded.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultithreadedLibrary.generated.h"
class MultithreadedTask : public FNonAbandonableTask {
public:
	MultithreadedTask(UObject* object) { this->object = object; }
	UObject* object;
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(MultithreadedTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork()
	{
		IMultithreaded::Execute_MultithreadedFunction(object);
	}
};

class MultithreadedCommandTask : public FNonAbandonableTask {
public:
	MultithreadedCommandTask(UObject* object, FString command) { this->object = object; this->command = command; }
	UObject* object;
	FString command;
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(MultithreadedTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork()
	{
		IMultithreaded::Execute_MultithreadedFunctionCommand(object, command);
	}
};

UCLASS()
class NEURALVISUE_API UMultithreadedLibrary : public UBlueprintFunctionLibrary {
	//Here you can see my project was named "My project" when this class was created in the unreal editor. 
	//so now this class is callled "MYPROJECT_API" after the project name it was created within.
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		static void CallMultithreadedFunction(UObject* object) {
		(new FAutoDeleteAsyncTask<MultithreadedTask>(object))->StartBackgroundTask();
	}
	
	UFUNCTION(BlueprintCallable)
		static void CallMultithreadedFunctionCommand(UObject* object, FString command) {
		(new FAutoDeleteAsyncTask<MultithreadedCommandTask>(object, command))->StartBackgroundTask();
	}
};

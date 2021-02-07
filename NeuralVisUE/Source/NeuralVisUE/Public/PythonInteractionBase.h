// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PythonInteractionBase.generated.h"

/**
 *
 */
UCLASS()
class NEURALVISUE_API UPythonInteractionBase : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Python Interaction Base")
		static FString HelloUnreal(int a, int b);
	
		UFUNCTION(BlueprintCallable, Category = "Python Interaction Base")
		static FString ExecuteCommand(FString command);
};

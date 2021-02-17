// Copyright Epic Games, Inc. All Rights Reserved.

#include "INeuralInteractionClientBPLibrary.h"
#include "INeuralInteractionClient.h"

UNeuralInteractionClientBPLibrary::UNeuralInteractionClientBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

/*float UNeuralInteractionClientBPLibrary::NeuralInteractionClientSampleFunction(float Param)
{
	return -1;
}*/

FString UNeuralInteractionClientBPLibrary::HelloUnreal(int a, int b)
{
	int foo = a + b;
	return (FString::Printf(TEXT("Hello Unreal. I calculated %d + %d = %d for you. Am I artificially intelligent yet?"), a, b, foo));
	//INeuralInteractionClient::Get().LoadClient();
}

FString UNeuralInteractionClientBPLibrary::ExecuteCommand(FString command)
{
	std::system(TCHAR_TO_ANSI(*command));
	INeuralInteractionClient::Get().LoadClient(command);
	return (command.Append(" was just executed."));
}

/*FString UNeuralInteractionClientBPLibrary::ExecuteCommandAdvanced(FString command, void (*processing)(FString))
{
	std::system(TCHAR_TO_ANSI(*command));
	return (command.Append(" was executed."));
}
*/
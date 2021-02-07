// Fill out your copyright notice in the Description page of Project Settings.


#include "PythonInteractionBase.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include <INeuralInteractionClient.h>

using namespace std;

FString UPythonInteractionBase::HelloUnreal(int a, int b)
{
	int foo = a + b;/**/
	return (FString::Printf(TEXT("Hello Unreal. I calculated %d + %d = %d for you. Am I artificially intelligent yet?"), a, b, foo));
	//INeuralInteractionClient::Get().LoadClient();
}

FString UPythonInteractionBase::ExecuteCommand(FString command)
{
	std::system(TCHAR_TO_ANSI(*command));
	INeuralInteractionClient::Get().LoadClient();
	return (command.Append(" was just executed."));
}

/*FString UPythonInteractionBase::ExecuteCommandAdvanced(FString command, void (*processing)(FString))
{
	std::system(TCHAR_TO_ANSI(*command));
	return (command.Append(" was executed."));
}
*/
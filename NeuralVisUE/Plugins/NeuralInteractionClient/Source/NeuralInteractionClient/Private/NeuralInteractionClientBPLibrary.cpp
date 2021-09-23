/*
This file NeuralInteractionClientBPLibrary.cpp is part of NeuralVisUAL.

NeuralVisUAL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

NeuralVisUAL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with NeuralVisUAL.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "INeuralInteractionClientBPLibrary.h"
#include "INeuralInteractionClient.h"

UNeuralInteractionClientBPLibrary::UNeuralInteractionClientBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

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

FString UNeuralInteractionClientBPLibrary::ExecuteCommandAdvanced(FString command, const FReadResponse& Callback)
{
	std::system(TCHAR_TO_ANSI(*command));
	INeuralInteractionClient::Get().LoadClientAdvanced(command, Callback);
	//Callback.Execute(TEXT("Delegate was just called."));
	return (command.Append(" was just executed."));
}

FString UNeuralInteractionClientBPLibrary::ExecuteCommandWithAllDelegates(FString command,
	const FEndOfConnection& CallbackEndOfConnection,
	const FStartOrEndOfResponse& CallbackStartOrEndOfResponse,
	const FParseError& CallbackParseError,
	const FStartOrEndOfMap& CallbackStartOrEndOfMap,
	const FStartOrEndOfArray& CallbackStartOrEndOfArray,
	const FFoundAtomNil& CallbackFoundAtomNil,
	const FFoundAtomString& CallbackFoundAtomString,
	const FFoundAtomBinary& CallbackFoundAtomBinary,
	const FFoundAtomExternal& CallbackFoundAtomExternal,
	const FFoundAtomBoolean& CallbackFoundAtomBoolean,
	const FFoundAtomInteger& CallbackFoundAtomInteger,
	const FFoundAtomInteger64& CallbackFoundAtomInteger64,
	const FFoundAtomFloat& CallbackFoundAtomFloat
)
{
	std::system(TCHAR_TO_ANSI(*command));
	INeuralInteractionClient::Get().LoadClientWithAllDelegates(command,
		CallbackEndOfConnection,
		CallbackStartOrEndOfResponse,
		CallbackParseError,
		CallbackStartOrEndOfMap,
		CallbackStartOrEndOfArray,
		CallbackFoundAtomNil,
		CallbackFoundAtomString,
		CallbackFoundAtomBinary,
		CallbackFoundAtomExternal,
		CallbackFoundAtomBoolean,
		CallbackFoundAtomInteger,
		CallbackFoundAtomInteger64,
		CallbackFoundAtomFloat
	);
	//Callback.Execute(TEXT("Delegate was just called."));
	return (command.Append(" was just executed."));
}

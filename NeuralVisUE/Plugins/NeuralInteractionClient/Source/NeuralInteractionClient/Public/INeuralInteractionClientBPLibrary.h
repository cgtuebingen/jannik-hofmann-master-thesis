/*
This file INeuralInteractionClientBPLibrary.h is part of NeuralVisUAL.

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

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "INeuralInteractionClientBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FReadResponse, FString, test);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FEndOfConnection, FString, originalCommand, bool, forciblyClosed);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FStartOrEndOfResponse, FString, originalCommand, FString, firstString, bool, endFlag);
DECLARE_DYNAMIC_DELEGATE_FourParams(FParseError, FString, originalCommand, FString, firstString, FString, arrayPosition, bool, dueToInsufficientBytes);
DECLARE_DYNAMIC_DELEGATE_FourParams(FStartOrEndOfMap, FString, originalCommand, FString, firstString, FString, arrayPosition, bool, endFlag);
DECLARE_DYNAMIC_DELEGATE_FourParams(FStartOrEndOfArray, FString, originalCommand, FString, firstString, FString, arrayPosition, bool, endFlag);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FFoundAtomNil, FString, originalCommand, FString, firstString, FString, arrayPosition);
DECLARE_DYNAMIC_DELEGATE_FourParams(FFoundAtomString, FString, originalCommand, FString, firstString, FString, arrayPosition, FString, content);
DECLARE_DYNAMIC_DELEGATE_FourParams(FFoundAtomBinary, FString, originalCommand, FString, firstString, FString, arrayPosition, FString, content);
DECLARE_DYNAMIC_DELEGATE_FourParams(FFoundAtomExternal, FString, originalCommand, FString, firstString, FString, arrayPosition, FString, content);
DECLARE_DYNAMIC_DELEGATE_FourParams(FFoundAtomBoolean, FString, originalCommand, FString, firstString, FString, arrayPosition, bool, content);
DECLARE_DYNAMIC_DELEGATE_FourParams(FFoundAtomInteger, FString, originalCommand, FString, firstString, FString, arrayPosition, int32, content);
DECLARE_DYNAMIC_DELEGATE_FourParams(FFoundAtomInteger64, FString, originalCommand, FString, firstString, FString, arrayPosition, int64, content);
DECLARE_DYNAMIC_DELEGATE_FourParams(FFoundAtomFloat, FString, originalCommand, FString, firstString, FString, arrayPosition, float, content);

UCLASS()
class UNeuralInteractionClientBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Neural Interaction Client")
	static FString HelloUnreal(int a, int b);

	UFUNCTION(BlueprintCallable, Category = "Neural Interaction Client")
	static FString ExecuteCommand(FString command);

	UFUNCTION(BlueprintCallable, Category = "Neural Interaction Client")
	static FString ExecuteCommandAdvanced(FString command, const FReadResponse& Callback);

	UFUNCTION(BlueprintCallable, Category = "Neural Interaction Client")
	static FString ExecuteCommandWithAllDelegates(FString command,
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
	);
};
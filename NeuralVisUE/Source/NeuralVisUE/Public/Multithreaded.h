/*
This file Multithreaded.h is part of NeuralVisUAL.

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
#include "UObject/Interface.h"
#include "Multithreaded.generated.h"
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMultithreaded : public UInterface
{
	GENERATED_BODY()
};
/**
 * 
 */
class NEURALVISUE_API IMultithreaded
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Multithreaded")
		void MultithreadedFunction();
		
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Multithreaded")
		void MultithreadedFunctionCommand(const FString& command);
};

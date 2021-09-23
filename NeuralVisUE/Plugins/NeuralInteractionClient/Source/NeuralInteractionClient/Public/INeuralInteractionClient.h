/*
This file INeuralInteractionClient.h is part of NeuralVisUAL.

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

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "INeuralInteractionClientBPLibrary.h"

class INeuralInteractionClient : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	//virtual void StartupModule() override;
	//virtual void ShutdownModule() override;

	static inline INeuralInteractionClient& Get()
	{
		return FModuleManager::LoadModuleChecked<INeuralInteractionClient>("NeuralInteractionClient");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("NeuralInteractionClient");
	}

	virtual int LoadClient(FString command) = 0;

	virtual int LoadClientAdvanced(FString command, const FReadResponse& Callback) = 0;

	virtual int LoadClientWithAllDelegates(FString command,
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
	) = 0;
};

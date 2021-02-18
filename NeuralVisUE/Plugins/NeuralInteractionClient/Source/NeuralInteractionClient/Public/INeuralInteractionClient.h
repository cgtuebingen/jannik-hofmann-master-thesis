// Copyright Epic Games, Inc. All Rights Reserved.

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
		const FEndOfReponse& CallbackEndOfReponse,
		const FParseError& CallbackParseError,
		const FStartOrEndOfMap& CallbackStartOrEndOfMap,
		const FStartOrEndOfNestedArray& CallbackStartOrEndOfNestedArray,
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

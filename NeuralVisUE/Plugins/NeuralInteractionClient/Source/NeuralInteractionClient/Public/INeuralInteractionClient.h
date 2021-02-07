// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

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
};

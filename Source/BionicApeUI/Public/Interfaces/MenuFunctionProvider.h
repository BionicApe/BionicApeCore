// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuFunctionProvider.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuFunctionProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BIONICAPEUI_API IMenuFunctionProvider
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Host(FString ServerName) = 0;
	virtual void Join(uint32 Index) = 0;
	virtual void RefreshServerList() = 0;
};

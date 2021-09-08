// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "BACameraOwner.generated.h"

class UInventory;
class AInventoryStore;
class UConfirmWidget;
class UAlertWidget;

/**
*
*/
UINTERFACE(Blueprintable)
class BIONICAPECORE_API UBACameraOwner : public UInterface
{
	GENERATED_BODY()
};

class IBACameraOwner
{
	GENERATED_BODY()

public:

	virtual bool IsViewTargetSetInCameraManager() const = 0;
};
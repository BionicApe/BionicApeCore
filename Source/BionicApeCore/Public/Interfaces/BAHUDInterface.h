// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "BAHUDInterface.generated.h"

class UInventory;
class AInventoryStore;
class UConfirmWidget;
class UAlertWidget;

/**
*
*/
UINTERFACE(Blueprintable)
class BIONICAPECORE_API UBAHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class IBAHUDInterface
{
	GENERATED_BODY()

public:

	virtual UAlertWidget* CreateAlert(const FText& Message) = 0;

	virtual UAlertWidget* NotifyResponse(bool bIsSuccessful, const FText& Message) = 0;

	virtual UConfirmWidget* CreateConfirm(const FText& Message) = 0;
};
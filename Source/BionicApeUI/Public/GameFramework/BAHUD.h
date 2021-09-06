// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interfaces/BAHUDInterface.h"
#include "BAHUD.generated.h"

class UBAUIConfig;
class UConfirmWidget;
class UAlertWidget;

/**
 *
 */
UCLASS()
class BIONICAPEUI_API ABAHUD : public AHUD, public IBAHUDInterface
{
	GENERATED_BODY()
public:

	static const FInputModeGameAndUI InputModeGameAndUI;
	static const FInputModeGameOnly InputModeGameOnly;

public:

	UFUNCTION(BlueprintCallable)
	void SetInputModeGameAndUI();

	UFUNCTION(BlueprintCallable)
	void SetInputModeGameOnly();

	//IBAHUDInterface
	UFUNCTION(BlueprintCallable)
	virtual UAlertWidget* CreateAlert(const FText& Message) override;

	UFUNCTION(BlueprintCallable)
	virtual UAlertWidget* NotifyResponse(bool bIsSuccessful, const FText& Message) override;

	UFUNCTION(BlueprintCallable)
	virtual UConfirmWidget* CreateConfirm(const FText& Message) override;
	//End IBAHUDInterface

};

// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MultiplayerMenuWidget.h"
#include "MultiplayerInGameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BIONICAPEUI_API UMultiplayerInGameMenuWidget : public UMultiplayerMenuWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UFUNCTION()
	void CancelPressed();

	UFUNCTION()
	void QuitPressed();
};

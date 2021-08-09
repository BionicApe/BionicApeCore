// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerMenuWidget.generated.h"

class IMenuFunctionProvider;
class UBionicApeUISubsystem;

/**
 *
 */
UCLASS()
class BIONICAPEUI_API UMultiplayerMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	virtual void RemoveFromParent() override;
		
protected:

	IMenuFunctionProvider* FunctionProvider;

	UBionicApeUISubsystem* UISubsystem;

};

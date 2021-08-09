// Created by Bionic Ape. All Rights Reserved.

#include "UI/MultiplayerInGameMenuWidget.h"
#include "Components/Button.h"
#include "Interfaces/MenuFunctionProvider.h"
#include "BionicApeUISubsystem.h"

bool UMultiplayerInGameMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMultiplayerInGameMenuWidget::CancelPressed);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMultiplayerInGameMenuWidget::QuitPressed);

	return true;
}

void UMultiplayerInGameMenuWidget::CancelPressed()
{
	RemoveFromParent();
}


void UMultiplayerInGameMenuWidget::QuitPressed()
{
	if (FunctionProvider) 
	{
		RemoveFromParent();
		UISubsystem->LoadMenu();
	}
}

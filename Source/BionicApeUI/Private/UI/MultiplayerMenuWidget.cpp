// Created by Bionic Ape. All Rights Reserved.


#include "UI/MultiplayerMenuWidget.h"
#include "Interfaces/MenuFunctionProvider.h"
#include "Blueprint/UserWidget.h"
#include "BionicApeUISubsystem.h"

bool UMultiplayerMenuWidget::Initialize()
{
	bool bSuperInitialize = Super::Initialize();

	if (bSuperInitialize)
	{

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return false;

		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (!ensure(PlayerController != nullptr)) return false;

		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(this->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = true;

		UGameInstance* GameInstance = GetGameInstance();
		if (!ensure(GameInstance != nullptr)) return false;

		UISubsystem = GameInstance->GetSubsystem<UBionicApeUISubsystem>();
		if (!ensure(UISubsystem != nullptr)) return false;

		FunctionProvider = UISubsystem->GetFunctionProvider();
		if (!ensure(FunctionProvider != nullptr)) return false;
	}

	return bSuperInitialize;
}

void UMultiplayerMenuWidget::RemoveFromParent()
{
	Super::RemoveFromParent();

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
}
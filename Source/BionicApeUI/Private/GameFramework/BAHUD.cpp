// Created by Bionic Ape. All Rights Reserved.


#include "GameFramework/BAHUD.h"
#include "BAUISubsystem.h"
#include "UI/AlertWidget.h"

const FInputModeGameAndUI ABAHUD::InputModeGameAndUI = FInputModeGameAndUI().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock).SetHideCursorDuringCapture(true);
const FInputModeGameOnly ABAHUD::InputModeGameOnly = FInputModeGameOnly();

#define LOCTEXT_NAMESPACE "BAHUD"

void ABAHUD::SetInputModeGameAndUI()
{
	if (APlayerController* PC = GetOwningPlayerController())
	{
		PC->SetInputMode(InputModeGameAndUI);
		PC->bShowMouseCursor = true;
	}
}

void ABAHUD::SetInputModeGameOnly()
{
	if (APlayerController* PC = GetOwningPlayerController())
	{
		PC->SetInputMode(InputModeGameOnly);
		PC->bShowMouseCursor = false;
	}
}

UAlertWidget* ABAHUD::CreateAlert(const FText& Message)
{
	UAlertWidget* AlertWidget = UBAUISubsystem::GetInstance()->CreateAlertWidget(GetOwningPlayerController(), Message);
	SetInputModeGameAndUI();
	return AlertWidget;
}

UAlertWidget* ABAHUD::NotifyResponse(bool bIsSuccessful, const FText& Message)
{
	return CreateAlert(bIsSuccessful ? LOCTEXT("NotifyResponse", "Successful") : Message);
}

UConfirmWidget* ABAHUD::CreateConfirm(const FText& Message)
{
	UE_LOG(LogTemp, Log, TEXT("UInventoryItemEntryListEntryStoreW::OnButtonPressed"));
	UConfirmWidget* AlertWidget = UBAUISubsystem::GetInstance()->CreateConfirmWidget(GetOwningPlayerController(), Message);
	SetInputModeGameAndUI();
	return AlertWidget;
}


#undef LOCTEXT_NAMESPACE // "BAHUD"


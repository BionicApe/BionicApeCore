// Created by Bionic Ape. All Rights Reserved.


#include "Components/ControlComponent.h"
#include "Interfaces/BAHUDInterface.h"
#include "GameFramework/HUD.h"


APlayerController* UControlComponent::GetController() const
{
	return Cast<APlayerController>(GetOwner());
}

APawn* UControlComponent::GetControlledPawn() const
	{
{
	if (APlayerController* PC = GetController())
		return PC->GetPawn();
	}
	return nullptr;
}

AHUD* UControlComponent::GetHUD() const
{
	if (APlayerController* PC = GetController())
	{
		return PC->GetHUD();
	}
	return nullptr;
}

TScriptInterface<IBAHUDInterface> UControlComponent::GetBAHUD() const
{
	return GetHUD();
}

void UControlComponent::Client_Notify_Implementation(bool bIsSuccessful, const FString& Message)
{
	TScriptInterface<IBAHUDInterface> BAHUD = GetBAHUD();
	if (BAHUD)
	{
		BAHUD->NotifyResponse(bIsSuccessful, FText::FromString(Message));
	}
}
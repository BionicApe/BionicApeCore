// Created by Bionic Ape. All Rights Reserved.


#include "Components/ControlComponent.h"


APlayerController* UControlComponent::GetController() const
{
	return Cast<APlayerController>(GetOwner());
}

AHUD* UControlComponent::GetHUD() const
{
	if (APlayerController* PC = GetController())
	{
		return PC->GetHUD();
	}
	return nullptr;
}

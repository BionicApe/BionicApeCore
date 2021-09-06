// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/BAHUDInterface.h"
#include "ControlComponent.generated.h"

class APlayerController;
class AHUD;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BIONICAPECORE_API UControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	APlayerController* GetController() const;

	UFUNCTION(BlueprintCallable)
	AHUD* GetHUD() const;

	TScriptInterface<IBAHUDInterface> GetBAHUD() const;

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_Notify(bool bIsSuccessful, const FString& Message);
};

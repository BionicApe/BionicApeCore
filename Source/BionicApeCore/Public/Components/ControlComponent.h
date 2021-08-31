// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
};

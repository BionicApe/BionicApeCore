// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BATPCharacter.generated.h"

UCLASS()
class BIONICAPECORE_API ABATPCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(Transient)
	APlayerCameraManager* CameraManagerCache;

public:
	// Sets default values for this character's properties
	ABATPCharacter();

	virtual void Restart() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveForward(float Val);
	virtual void MoveRight(float Val);
};

<<<<<<< HEAD
// Created by Bionic Ape. All rights reseved.
=======
>>>>>>> 8ad7dae00ab95cf7f474e123e83830c2f8250084

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPPCharacter.generated.h"

UCLASS()
class BIONICAPECORE_API AFPPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPPCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

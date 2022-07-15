
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

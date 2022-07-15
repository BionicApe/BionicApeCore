// Created by Bionic Ape. All rights reseved.


#include "GameFramework/FPPCharacter.h"
#include "Components/InputComponent.h"

// Sets default values
AFPPCharacter::AFPPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//InputComponent->BindAxis("MoveForward", this, &AFPPCharacter::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &AFPPCharacter::MoveRight);
}


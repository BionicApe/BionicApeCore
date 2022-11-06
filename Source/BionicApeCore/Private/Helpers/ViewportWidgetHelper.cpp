// Created by Bionic Ape. All Rights Reserved.


#include "Helpers/ViewportWidgetHelper.h"
#include "Camera/Cameracomponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/ChildActorComponent.h"

// Sets default values
AViewportWidgetHelper::AViewportWidgetHelper()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->RotationRate.Yaw = 40.f;
	
	ChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	ChildActor->SetupAttachment(RootComponent);
}



void AViewportWidgetHelper::SetNewObject(UObject* NewObj)
{
	OnNewObject(NewObj);
}

void AViewportWidgetHelper::SpawnChildActor(TSubclassOf<AActor> Class)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		//TODO: LOG
		return;
	}

	ChildActor->SetChildActorClass(Class);
}

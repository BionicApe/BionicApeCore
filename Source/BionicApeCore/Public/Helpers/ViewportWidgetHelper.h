// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewportWidgetHelper.generated.h"

class UCameraComponent;
class URotatingMovementComponent;

UCLASS()
class BIONICAPECORE_API AViewportWidgetHelper : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	URotatingMovementComponent* RotatingMovementComponent;

public:	
	// Sets default values for this actor's properties
	AViewportWidgetHelper();

	UFUNCTION(BlueprintImplementableEvent, Category = "Viewport")
	void OnNewObject(UObject* NewObj);

	virtual void SetNewObject(UObject* NewObj);
};

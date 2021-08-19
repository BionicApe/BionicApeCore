// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "ActorActionUtility.h"
#include "Materials/MaterialInterface.h"
#include "MyActorActionUtility.generated.h"

/**
 * 
 */
UCLASS()
class BIONICAPEEDITOR_API UMyActorActionUtility : public UActorActionUtility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(CallInEditor)
	void ChangeMaterial(UMaterialInterface* NewMaterial);

};

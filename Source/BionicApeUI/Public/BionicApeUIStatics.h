// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BionicApeUIStatics.generated.h"

class APlayerController;

UCLASS()
class BIONICAPEUI_API UBionicApeUIStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void CalculatePositionInViewport(APlayerController* PlayerController, float const SizeX, float const SizeY, FVector2D& Result);

};
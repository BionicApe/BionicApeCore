// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseEditorTool.h"
#include "UObject/NoExportTypes.h"
#include "BAMirrorTool.generated.h"

/**
 *
 */
UCLASS()
class BIONICAPEEDITOR_API UBAMirrorTool : public UBaseEditorTool
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, Category = "Settings")
	FPlane MirrorPlane;

	UFUNCTION(Exec, Category = "Settings")
	void MirrorSelectedObjects();

};

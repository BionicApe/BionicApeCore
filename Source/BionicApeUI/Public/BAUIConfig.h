// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BAUIConfig.generated.h"

class UAlertWidget;
class UButtonStyleAsset;
class UConfirmWidget;

/**
 * 
 */
UCLASS()
class BIONICAPEUI_API UBAUIConfig : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UAlertWidget> AlertWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UAlertWidget> SuccessAlertWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UAlertWidget> FailureAlertWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UConfirmWidget> ConfirmWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	UButtonStyleAsset* ButtonStyleNormal;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	UButtonStyleAsset* ButtonStyleHover;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	UButtonStyleAsset* ButtonStylePressed;
	
};

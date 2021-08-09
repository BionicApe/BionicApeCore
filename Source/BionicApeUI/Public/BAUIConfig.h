// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BAUIConfig.generated.h"

class UAlertWidget;

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
	
};

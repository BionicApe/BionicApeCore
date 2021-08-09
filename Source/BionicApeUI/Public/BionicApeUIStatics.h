// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BionicApeUIStatics.generated.h"

class APlayerController;
class UCategoryTabWidget;
class UObject;
class UWidget;
class UHorizontalBox;

UCLASS()
class BIONICAPEUI_API UBionicApeUIStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void CalculatePositionInViewport(APlayerController* PlayerController, float const SizeX, float const SizeY, FVector2D& Result);

	UFUNCTION(BlueprintCallable, Category = "BionicApeUI")
	static UCategoryTabWidget* CreateTab(
		TSubclassOf<UCategoryTabWidget> TabWidgetClass,
		FText TabText,
		UWidgetSwitcher* TabContentSwitcher,
		UHorizontalBox* TabsWidget,
		UWidget* ContentWidget);

	UFUNCTION(BlueprintCallable, Category = "BionicApeUI")
	static void OnTabSelected(
		UWidgetSwitcher* TabContentSwitcher,
		UHorizontalBox* TabsWidget,
		UCategoryTabWidget* SelectedTabWidget,
		UWidget* SelectedContentWidget);

};
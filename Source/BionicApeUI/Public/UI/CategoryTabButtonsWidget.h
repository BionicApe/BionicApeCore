// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/UserWidget.h"
#include "CategoryTabButtonsWidget.generated.h"

class UListView;
class UCategoryTabWidget;
class UTextBlock;
class UWidgetSwitcher;

/**
 *
 */
UCLASS()
class BIONICAPEUI_API UCategoryTabButtonsWidget : public UHorizontalBox
{
	GENERATED_BODY()

public:

	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	//TArray<UCategoryTabWidget*> TabWidgetsArray;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//UWidgetSwitcher* TabContentSwitcher;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//UTextBlock* CategorySelectedText;


public:

	//virtual void ClearChildren() override;

	//UFUNCTION(BlueprintCallable)
	//UCategoryTabWidget* AddChildToCategoryTab(UCategoryTabWidget* TabWidget);

	//UFUNCTION(BlueprintImplementableEvent)
	//void SetupHorizontalSlotValues(UHorizontalBoxSlot* HorizontalBoxSlot);
	//
	//UFUNCTION()
	//void OnTabSelected(UCategoryTabWidget* SelectedCategoryTabWidget);
};

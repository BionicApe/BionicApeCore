// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BionicApeUIStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerController.h"
#include "UI/CategoryTabWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"

void UBionicApeUIStatics::CalculatePositionInViewport(APlayerController* PlayerController, float const WidgetSizeX, float const WidgetSizeY, FVector2D& Result)
{
	float MouseScaledX, MouseScaledY;
	UWidgetLayoutLibrary::GetMousePositionScaledByDPI(PlayerController, MouseScaledX, MouseScaledY);

	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(PlayerController);

	Result.X = FMath::Clamp(MouseScaledX - WidgetSizeX / 2, 0.f, ViewportSizeX / ViewportScale - WidgetSizeX);
	Result.Y = FMath::Clamp(MouseScaledY - WidgetSizeY / 2, 0.f, ViewportSizeY / ViewportScale - WidgetSizeY);
}

UCategoryTabWidget* UBionicApeUIStatics::CreateTab(
	TSubclassOf<UCategoryTabWidget> TabWidgetClass,
	FText TabText,
	UWidgetSwitcher* TabContentSwitcher,
	UHorizontalBox* TabsWidget,
	UWidget* ContentWidget
)
{
	//Create Button for the tab
	if (UCategoryTabWidget* TabWidget = CreateWidget<UCategoryTabWidget>(TabsWidget, TabWidgetClass))
	{
		TabWidget->SetTabText(TabText);

		TabWidget->OnChanged().AddLambda([TabContentSwitcher, TabsWidget, TabWidget, ContentWidget]()
			{
				UBionicApeUIStatics::OnTabSelected(TabContentSwitcher, TabsWidget, TabWidget, ContentWidget);
			});

		//Add Tab Button to the horizontal box
		UHorizontalBoxSlot* HorizontalBoxSlot = TabsWidget->AddChildToHorizontalBox(TabWidget);
		return TabWidget;
	}
	
	return nullptr;
}

void UBionicApeUIStatics::OnTabSelected(
	UWidgetSwitcher* TabContentSwitcher,
	UHorizontalBox* TabsWidget,
	UCategoryTabWidget* SelectedTabWidget,
	UWidget* SelectedContentWidget)
{
	TabContentSwitcher->SetActiveWidget(SelectedContentWidget);

	TArray<UWidget*> ChildrenWidgets = TabsWidget->GetAllChildren();
	for (UWidget* ChildWidget : ChildrenWidgets)
	{
		if (UCategoryTabWidget* TabWidget = Cast<UCategoryTabWidget>(ChildWidget))
		{
			if (TabWidget == SelectedTabWidget)
			{
				TabWidget->SetStyleSelected();
			}
			else
			{
				TabWidget->SetStyleNotSelected();
			}
		}
	}
}
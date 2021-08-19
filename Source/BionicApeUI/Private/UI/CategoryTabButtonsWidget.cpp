// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CategoryTabButtonsWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "UI/CategoryTabWidget.h"
#include "UI/CategoryTabContentWidget.h"
//
//void UCategoryTabButtonsWidget::ClearChildren()
//{
//	Super::ClearChildren();
//	TabWidgetsArray.Empty();
//}
//
//UCategoryTabWidget* UCategoryTabButtonsWidget::AddChildToCategoryTab(UCategoryTabWidget* TabWidget)
//{
//	//Create Button for the tab
//	if (TabWidget)
//	{
//		TabWidgetsArray.Add(TabWidget);
//
//		UHorizontalBoxSlot* HorizontalBoxSlot = AddChildToHorizontalBox(TabWidget);
//		SetupHorizontalSlotValues(HorizontalBoxSlot);
//		TabWidget->OnChanged().AddUObject(this, &UCategoryTabButtonsWidget::OnTabSelected);
//
//		//Hack to set the correct values
//		if (TabWidgetsArray.Num() == 1)
//		{
//			TabWidget->SetStyleSelected();
//		}
//
//		return TabWidget;
//	}
//	return nullptr;
//}
//
//void UCategoryTabButtonsWidget::OnTabSelected(UCategoryTabWidget* SelectedCategoryTabWidget)
//{
//	if (SelectedCategoryTabWidget)
//	{
//		for (UCategoryTabWidget* TabWidget : TabWidgetsArray)
//		{
//			if (TabWidget == SelectedCategoryTabWidget)
//			{
//				TabWidget->SetStyleSelected();
//			}
//			else
//			{
//				TabWidget->SetStyleNotSelected();
//			}
//		}
//
//		if (CategorySelectedText)
//		{
//			CategorySelectedText->SetText(SelectedCategoryTabWidget->TabCategoryName);
//		}
//
//		if (TabContentSwitcher)
//		{
//			TabContentSwitcher->SetActiveWidget(SelectedCategoryTabWidget->ContentWidget);
//		}
//	}
//}

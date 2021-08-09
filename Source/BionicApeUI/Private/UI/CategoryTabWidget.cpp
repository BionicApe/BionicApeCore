// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CategoryTabWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UCategoryTabWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (TabTextBlock && TabButton)
		{
			TabButton->OnClicked.AddDynamic(this, &UCategoryTabWidget::OnButtonClicked);
			return true;
		}
	}
	return false;
}

void UCategoryTabWidget::OnButtonClicked()
{
	TabSelectedEvent.Broadcast();
}

void UCategoryTabWidget::SetTabText(FText TabText)
{
	if (TabTextBlock)
	{
		TabTextBlock->SetText(TabText);
	}
}

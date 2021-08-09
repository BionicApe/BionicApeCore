// Created by Bionic Ape. All Rights Reserved.


#include "UI/ConfirmWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UConfirmWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (!AcceptButton) return false;
		if (!BodyText) return false;
		if (!CancelButton) return false;
		
		AcceptButton->OnClicked.AddDynamic(this, &UConfirmWidget::OnAcceptButtonClicked);
		CancelButton->OnClicked.AddDynamic(this, &UConfirmWidget::OnCancelButtonClicked);
	}
	return false;
}

void UConfirmWidget::SetBodyText(const FText& NewText)
{
	BodyText->SetText(NewText);
}

void UConfirmWidget::OnAcceptButtonClicked()
{
	OnFinishConfirmWidget.Broadcast(true);
	RemoveFromViewport();
}

void UConfirmWidget::OnCancelButtonClicked()
{
	OnFinishConfirmWidget.Broadcast(false);
	RemoveFromViewport();
}

// Created by Bionic Ape. All Rights Reserved.


#include "UI/AlertWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UAlertWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (!AcceptButton) return false;
		if (!BodyText) return false;
				
		AcceptButton->OnClicked.AddDynamic(this, &UAlertWidget::OnAcceptButtonClicked);
	}
	return false;
}

void UAlertWidget::SetBodyText(const FText& NewText)
{
	BodyText->SetText(NewText);
}

void UAlertWidget::OnAcceptButtonClicked()
{
	RemoveFromViewport();
}
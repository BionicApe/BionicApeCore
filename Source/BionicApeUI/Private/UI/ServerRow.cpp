// Created by Bionic Ape. All Rights Reserved.

#include "UI/ServerRow.h"
#include "UI/MultiplayerMainMenuWidget.h"
#include "Components/Button.h"


void UServerRow::Setup(class UMultiplayerMainMenuWidget* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	Parent->SelectIndex(Index);
}




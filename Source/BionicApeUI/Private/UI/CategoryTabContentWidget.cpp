// Created by Bionic Ape. All rights reseved.


#include "UI/CategoryTabContentWidget.h"

#include "Components/ListView.h"

bool UCategoryTabContentWidget::Initialize()
{
	if (!Super::Initialize())
	{
		UE_LOG(LogTemp, Error, TEXT("UCategoryTabContentWidget::Initialize() Super::Initialize failed"));
		return false;
	}

	if (!ListViewWidget)
	{
		UE_LOG(LogTemp, Log, TEXT("UCategoryTabContentWidget::Initialize() ListViewWidget is not bound"));
		return false;
	}

	//This is because if it's false we can't have buttons inside the items in the ListViewWidget
	//ListViewWidget->bClearSelectionOnClick = false;

	return true;
}

void UCategoryTabContentWidget::SetListItems(const TArray<UObject*>& Items)
{
	ListViewWidget->SetListItems(Items);
}

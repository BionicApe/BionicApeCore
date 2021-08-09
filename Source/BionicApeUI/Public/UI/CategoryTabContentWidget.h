// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CategoryTabContentWidget.generated.h"

class UListView;


/**
 *
 */
UCLASS()
class BIONICAPEUI_API UCategoryTabContentWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UListView* ListViewWidget;

public:

	virtual bool Initialize() override
	{
		return Super::Initialize() && ListViewWidget;
	}
};

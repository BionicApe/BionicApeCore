// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AlertWidget.generated.h"

class UButton;
class UTextBlock;


/**
 * 
 */
UCLASS()
class BIONICAPEUI_API UAlertWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* AcceptButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BodyText;

protected:

	virtual bool Initialize() override;

public:

	UFUNCTION(BlueprintCallable)
	void SetBodyText(const FText& NewText);
		
	UFUNCTION()
	void OnAcceptButtonClicked();
};

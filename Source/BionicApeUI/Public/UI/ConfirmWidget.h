// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishConfirmWidget, bool, bIsSuccessful);

class UButton;
class UTextBlock;


/**
 * 
 */
UCLASS()
class BIONICAPEUI_API UConfirmWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* AcceptButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BodyText;
public:

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnFinishConfirmWidget OnFinishConfirmWidget;

protected:

	virtual bool Initialize() override;

public:

	UFUNCTION(BlueprintCallable)
	void SetBodyText(const FText& NewText);
	
	UFUNCTION()
	void OnAcceptButtonClicked();

	UFUNCTION()
	void OnCancelButtonClicked();
};

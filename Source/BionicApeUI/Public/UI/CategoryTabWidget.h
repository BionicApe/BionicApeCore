// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CategoryTabWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class BIONICAPEUI_API UCategoryTabWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UButton* TabButton;

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextBlock* TabTextBlock;

public:

	DECLARE_EVENT(FCCOnTabSelectedDelegate, FCCTabSelectedEvent)
	FCCTabSelectedEvent& OnChanged() { return TabSelectedEvent; }

private:

	FCCTabSelectedEvent TabSelectedEvent;

public:
	
	virtual bool Initialize() override;

	void SetTabText(FText TabText);

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void SetStyleSelected();

	UFUNCTION(BlueprintImplementableEvent)
	void SetStyleNotSelected();
};

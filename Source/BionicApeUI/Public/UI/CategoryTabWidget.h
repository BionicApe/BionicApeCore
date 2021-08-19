// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BionicApeUIStatics.h"
#include "CategoryTabWidget.generated.h"

class UButton;
class UTextBlock;
class UButtonStyleAsset;
class UObject;
class UCategoryTabContentWidget;

/**
 * 
 */
UCLASS()
class BIONICAPEUI_API UCategoryTabWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UButton* TabButton;

	UPROPERTY(meta = (BindWidgetOptional), VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextBlock* TabTextBlock;

	UPROPERTY(EditDefaultsOnly)
	FText TabCategoryName;

	UPROPERTY()
	UObject* ResourceObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FButtonStyle ButtonStyleSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FButtonStyle ButtonStyleNotSelected;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UCategoryTabContentWidget* ContentWidget;

#pragma region TabSelectedEvent
public:
	DECLARE_EVENT_OneParam(FCCOnTabSelectedDelegate, FCCTabSelectedEvent, UCategoryTabWidget* SelectedWidget)
	FCCTabSelectedEvent& OnChanged() { return TabSelectedEvent; }
private:
	FCCTabSelectedEvent TabSelectedEvent;
#pragma endregion

public:
	
	virtual bool Initialize() override;

	void Setup(const FText& TabCategoryName, UObject* ResourceObject);

	void Refresh();
	
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void SetStyleSelected();

	UFUNCTION(BlueprintImplementableEvent)
	void SetStyleNotSelected();
};

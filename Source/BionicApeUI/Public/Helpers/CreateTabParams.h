// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateTabParams.generated.h"

class UCategoryTabWidget;
class UObject;
class UWidget;
class UHorizontalBox;
class UTextBlock;
class UWidgetSwitcher;

//USTRUCT(BlueprintType)
//struct BIONICAPEUI_API FCreateTabParams
//{
//	GENERATED_BODY()
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	TSubclassOf<UCategoryTabWidget> TabWidgetClass;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	UWidgetSwitcher* TabContentSwitcher;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	UHorizontalBox* TabsWidget;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	UWidget* ContentWidget;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	UTextBlock* CategorySelectedText;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	FText TabCategoryName;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	UObject* ResourceObject;
//
//	FCreateTabParams() :
//		TabWidgetClass(nullptr),
//		TabContentSwitcher(nullptr),
//		TabsWidget(nullptr),
//		ContentWidget(nullptr),
//		CategorySelectedText(nullptr),
//		ResourceObject(nullptr)
//
//	{
//
//	}
//
//	//FCreateTabParams(
//	//	TSubclassOf<UCategoryTabWidget> NewTabWidgetClass,
//	//	UWidgetSwitcher* NewTabContentSwitcher,
//	//	UHorizontalBox* NewTabsWidget,
//	//	UWidget* NewContentWidget,
//	//	FText NewTabText,
//	//	UTextBlock* NewSelectedCategoryText = nullptr,
//	//	UObject* NewResourceObject = nullptr) :
//	//	TabWidgetClass(NewTabWidgetClass),
//	//	TabContentSwitcher(NewTabContentSwitcher),
//	//	TabsWidget(NewTabsWidget),
//	//	ContentWidget(NewContentWidget),
//	//	TabCategoryName(NewTabText),
//	//	CategorySelectedText(NewSelectedCategoryText),
//	//	ResourceObject(NewResourceObject)
//	//{
//	//}
//};


USTRUCT(BlueprintType)
struct BIONICAPEUI_API FCreateCategoryTabParams
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCategoryTabWidget* TabWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWidget* ContentWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText TabCategoryName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UObject* ResourceObject;


	FCreateCategoryTabParams() :
		TabWidget(nullptr),
		ContentWidget(nullptr),
		ResourceObject(nullptr)
	{

	}

	FCreateCategoryTabParams(
		UWidget* NewContentWidget,
		FText NewTabCategoryName,
		UObject* NewResourceObject) :
		ContentWidget(NewContentWidget),
		TabCategoryName(NewTabCategoryName),
		ResourceObject(NewResourceObject)
	{
	}
};
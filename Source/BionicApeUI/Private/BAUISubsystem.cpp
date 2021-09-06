// Created by Bionic Ape. All Rights Reserved.


#include "BAUISubsystem.h"
#include "BAUIConfig.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/GameInstance.h"
#include "UI/AlertWidget.h"
#include "BAUIConfig.h"
#include "UI/ConfirmWidget.h"

UBAUISubsystem* UBAUISubsystem::MyInstance;

UBAUISubsystem::UBAUISubsystem() :Super()
{
	//We set default values that can be overridden by UsersProxy and ProfilesProxy, we can safely delete the following lines if the config file is correct
	static ConstructorHelpers::FObjectFinder<UBAUIConfig> BAUIConfigRef(TEXT("/BionicApeCore/UIConfig.UIConfig"));
	UIConfig = BAUIConfigRef.Object;
}

void UBAUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

	Super::Initialize(Collection);

	MyInstance = this;

	if (!UIConfigProxy.IsNull())
	{
		UIConfig = UIConfigProxy.LoadSynchronous();
	}
}

template <typename OwnerTy /*= UObject*/>
UAlertWidget* UBAUISubsystem::CreateAlertWidget(OwnerTy* Owner, const FText& Text)
{
	static_assert(TIsDerivedFrom<OwnerTy, UWidget>::IsDerived
		|| TIsDerivedFrom<OwnerTy, UWidgetTree>::IsDerived
		|| TIsDerivedFrom<OwnerTy, APlayerController>::IsDerived
		|| TIsDerivedFrom<OwnerTy, UGameInstance>::IsDerived
		|| TIsDerivedFrom<OwnerTy, UWorld>::IsDerived, "The given OwningObject is not of a supported type for use with CreateWidget.");

	UAlertWidget* AlertWidget = CreateWidget<UAlertWidget>(Owner, UBAUISubsystem::GetInstance()->UIConfig->SuccessAlertWidgetClass);
	AlertWidget->SetBodyText(Text);
	AlertWidget->AddToViewport();
	return AlertWidget;
}

UAlertWidget* UBAUISubsystem::CreateAlert(UUserWidget* Owner, const FText& Text)
{
	return CreateAlertWidget(Owner,Text);
}

template <typename OwnerTy /*= UObject*/>
UConfirmWidget* UBAUISubsystem::CreateConfirmWidget(OwnerTy* Owner, const FText& Text)
{
	static_assert(TIsDerivedFrom<OwnerTy, UWidget>::IsDerived
		|| TIsDerivedFrom<OwnerTy, UWidgetTree>::IsDerived
		|| TIsDerivedFrom<OwnerTy, APlayerController>::IsDerived
		|| TIsDerivedFrom<OwnerTy, UGameInstance>::IsDerived
		|| TIsDerivedFrom<OwnerTy, UWorld>::IsDerived, "The given OwningObject is not of a supported type for use with CreateWidget.");

	UConfirmWidget* ConfirmWidget = CreateWidget<UConfirmWidget>(Owner, UBAUISubsystem::GetInstance()->UIConfig->ConfirmWidgetClass);
	ConfirmWidget->SetBodyText(Text);
	ConfirmWidget->AddToViewport();
	return ConfirmWidget;
}

UConfirmWidget* UBAUISubsystem::CreateConfirm(UUserWidget* Owner, const FText& Text)
{
	return CreateConfirmWidget(Owner,Text);
}
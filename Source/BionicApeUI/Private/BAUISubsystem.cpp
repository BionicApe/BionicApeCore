// Created by Bionic Ape. All Rights Reserved.


#include "BAUISubsystem.h"
#include "BAUIConfig.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/GameInstance.h"
#include "UI/AlertWidget.h"
#include "BAUIConfig.h"

UBAUISubsystem* UBAUISubsystem::MyInstance;

UBAUISubsystem::UBAUISubsystem() :Super()
{
	//We set default values that can be overridden by UsersProxy and ProfilesProxy, we can safely delete the following lines if the config file is correct
	static ConstructorHelpers::FObjectFinder<UBAUIConfig> BAUIConfigRef(TEXT("/BionicApeUI/UIConfig.UIConfig"));
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

UAlertWidget* UBAUISubsystem::CreateAlert(UUserWidget* Owner, const FText& Text)
{
	UAlertWidget* AlertWidget = CreateWidget<UAlertWidget>(Owner, UBAUISubsystem::GetInstance()->UIConfig->SuccessAlertWidgetClass);
	AlertWidget->SetBodyText(Text);
	AlertWidget->AddToViewport();
	return AlertWidget;
}
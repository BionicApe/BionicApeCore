// Created by Bionic Ape. All Rights Reserved.


#include "BionicApeUISubsystem.h"
#include "BionicApeUI.h"
#include "Interfaces/MenuFunctionProvider.h"
#include "Blueprint/UserWidget.h"

UBionicApeUISubsystem::UBionicApeUISubsystem() :Super()
{
	
}

void UBionicApeUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogBionicApeUI, Log, TEXT("BionicApeUISubsystem Initialize"));

	UGameInstance* const MyGameInstance = GetGameInstance();

	if (MyGameInstance && MyGameInstance->Implements<UMenuFunctionProvider>())
	{
		FunctionProvider = Cast<IMenuFunctionProvider>(MyGameInstance);
	}
	else
	{
		UE_LOG(LogBionicApeUI, Error, TEXT("BionicApeUISubsystem GameInstance does not implements IMenuFunctionProvider"));
	}
}

void UBionicApeUISubsystem::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	UUserWidget* Menu = CreateWidget<UUserWidget>(GetGameInstance(), MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->AddToViewport();
}

void UBionicApeUISubsystem::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	UUserWidget* Menu = CreateWidget<UUserWidget>(GetGameInstance(), InGameMenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->AddToViewport();
}
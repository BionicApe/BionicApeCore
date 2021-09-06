// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "BAUISubsystem.generated.h"

class UBAUIConfig;
class UAlertWidget;
class UWidget;
class UConfirmWidget;
class OwnerTy;

/**
 *
 */
UCLASS(Config = BionicApe)
class BIONICAPEUI_API UBAUISubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	static UBAUISubsystem* MyInstance;

	UPROPERTY(BlueprintReadOnly)
	UBAUIConfig* UIConfig;

private:

	UPROPERTY(Config)
	TSoftObjectPtr<UBAUIConfig> UIConfigProxy;

public:

	UBAUISubsystem();

	static UBAUISubsystem* GetInstance() { return MyInstance; }

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	template <typename OwnerTy = UObject>
	static UAlertWidget* CreateAlertWidget(OwnerTy* Owner, const FText& Text);
	UFUNCTION(BlueprintCallable)
	static UAlertWidget* CreateAlert(UUserWidget* Owner, const FText& Text);

	template <typename OwnerTy = UObject>
	static UConfirmWidget* CreateConfirmWidget(OwnerTy* Owner, const FText& Text);
	UFUNCTION(BlueprintCallable)
	static UConfirmWidget* CreateConfirm(UUserWidget* Owner, const FText& Text);

};
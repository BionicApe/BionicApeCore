// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BionicApeUISubsystem.generated.h"

class UUserWidget;
class IMenuFunctionProvider;

/**
 * 
 */
UCLASS(Config = BionicApe)
class BIONICAPEUI_API UBionicApeUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(Config)
	TSubclassOf<class UUserWidget> MenuClass;
	
	UPROPERTY(Config)
	TSubclassOf<class UUserWidget> InGameMenuClass;

	IMenuFunctionProvider* FunctionProvider;

public:

	UBionicApeUISubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();
	
	IMenuFunctionProvider* GetFunctionProvider() const { return FunctionProvider; }
};

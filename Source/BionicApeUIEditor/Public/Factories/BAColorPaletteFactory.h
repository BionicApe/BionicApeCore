// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BAColorPaletteFactory.generated.h"

/**
*
*/
UCLASS()
class BIONICAPEUIEDITOR_API UBAColorPaletteFactory : public UFactory
{
	GENERATED_BODY()


	UBAColorPaletteFactory(const FObjectInitializer& ObjectInitializer);

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override { return true; }
	// End of UFactory interface

};

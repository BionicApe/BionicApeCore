// Created by Bionic Ape. All Rights Reserved.

#include "Factories/BAColorPaletteFactory.h"
#include "BAColorPalette.h"

UBAColorPaletteFactory::UBAColorPaletteFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	SupportedClass = UBAColorPalette::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UBAColorPaletteFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
	UBAColorPalette* NewAsset = NewObject<UBAColorPalette>(InParent, Class, Name, Flags);
	return NewAsset;
}



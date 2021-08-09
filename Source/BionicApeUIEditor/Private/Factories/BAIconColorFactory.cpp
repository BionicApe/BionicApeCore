// Created by Bionic Ape. All Rights Reserved.

#include "Factories/BAIconColorFactory.h"
#include "BAIconColor.h"

UBAIconColorFactory::UBAIconColorFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	SupportedClass = UBAIconColor::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UBAIconColorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
	UBAIconColor* NewAsset = NewObject<UBAIconColor>(InParent, Class, Name, Flags);
	return NewAsset;
}



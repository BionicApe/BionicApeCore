//// Created by Bionic Ape. All Rights Reserved.
//
//#include "Factories/BAMaterialParameterCollectionFactory.h"
//#include "Materials/BAMaterialParameterCollection.h"
//
//UBAMaterialParameterCollectionFactory::UBAMaterialParameterCollectionFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
//	SupportedClass = UBAMaterialParameterCollection::StaticClass();
//	bCreateNew = true;
//	bEditAfterNew = true;
//}
//
//UObject* UBAMaterialParameterCollectionFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
//	UBAMaterialParameterCollection* NewAsset = NewObject<UBAMaterialParameterCollection>(InParent, Class, Name, Flags);
//	return NewAsset;
//}
//
//

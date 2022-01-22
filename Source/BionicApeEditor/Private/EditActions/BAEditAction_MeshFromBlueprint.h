 // Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtractOptions.h"

class AActor;
class UWorld;
class UClass;

class FBAEditAction_MeshFromBlueprint
{
public:

	static const TSet<FString> IgnoreClassNames;
	static const TSet<UClass*> IgnoreClasses;

	static void ExecuteAction();
	
	static void SpawnActorsFromComponents(AActor* Actor, UWorld* World, UClass* ChosenClass);

	static bool IgnoreActor(AActor* Actor);
};
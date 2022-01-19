// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class AActor;
class UWorld;
class UClass;


class FBAEditActionsLib
{

public:
	
	static bool SpawnActorsFromComponents(AActor* Actor, UWorld* World, UClass* ChosenClass, bool const bSpawnOneActorPerComp = false, bool const bUseLevelNameAsRootFolder = true);
	static FName CreateFolderPath(AActor* Actor, UClass* ChosenClass, bool const bUseLevelNameAsRootFolder = true);
	static bool HasConstructorComponents(AActor* Actor);
};
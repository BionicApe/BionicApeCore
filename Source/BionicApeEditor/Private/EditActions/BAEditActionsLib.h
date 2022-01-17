// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class AActor;
class UWorld;
class UClass;


class FBAEditActionsLib
{

public:
	
	static bool SpawnActorsFromComponents(AActor* Actor, UWorld* World, UClass* ChosenClass, bool const bSpawnOneActorPerComp = false);

};
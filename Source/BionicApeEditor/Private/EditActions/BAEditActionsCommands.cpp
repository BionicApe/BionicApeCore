// Created by Bionic Ape. All Rights Reserved.

#include "BAEditActionsCommands.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "PltSimEditorModule"

void FBAEditActionsCommands::RegisterCommands()
{
	UI_COMMAND(ExtractStaticMesh, "Create StaticMeshActors from Actors", "Create StaticMeshActors from Actors", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ActorsFromSelection, "Create Actors From Selection", "Create Actors from the selection extracting components and adding them to the newly created Actor", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(RenameSelectedActors, "Rename Selected Actors", "Rename Selected Actors", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(CountSelectedActors, "Count Selected Actors", "Count Selected Actors", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

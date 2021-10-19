// Created by Bionic Ape. All Rights Reserved.

#include "BionicApeEditorCommands.h"

#define LOCTEXT_NAMESPACE "BionicApeEditorCommands"

void FBionicApeEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Bionic Ape Editor", "Open Bionic Ape Plugin window", EUserInterfaceActionType::Button, FInputChord());
	//UI_COMMAND(OpenModuleGeneratorTool, "Module Generator", "Bring up ModuleGenerator window", EUserInterfaceActionType::Button, FInputChord());
	//UI_COMMAND(NewModule, "New C++ module...", "Creates a new game module in this project", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
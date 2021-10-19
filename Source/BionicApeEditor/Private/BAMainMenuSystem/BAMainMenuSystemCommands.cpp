// Created by Bionic Ape. All Rights Reserved.

#include "BAMainMenuSystem/BAMainMenuSystemCommands.h"

#define LOCTEXT_NAMESPACE "BAMainMenuSystemCommands"

void FBAMainMenuSystemCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Bionic Ape Editor", "Open Bionic Ape Plugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "BionicApeEditor.h"
#include "BionicApeEditorEdMode.h"
#include "BionicApeEditorCommands.h"

#include "BAMainMenuSystem/BAMainMenuSystem.h"

#include "ModuleEditorTool.h"
#include "LevelEditor.h"

#include "ModuleGeneratorToolDetails.h"

#include "CoreMinimal.h"

#include "ToolMenu.h"
#include "ToolMenus.h"


#include "Widgets/Docking/SDockTab.h"
#include "Interfaces/IMainFrameModule.h"


static const FName BionicApeEditorTabName("BionicApeEditorTab");

#define LOCTEXT_NAMESPACE "BionicApeEditorModule"

void FBionicApeEditorModule::StartupModule()
{
	//Style
	FBionicApeEditorStyle::Initialize();
	FBionicApeEditorStyle::ReloadTextures();
	//End Style

	//EditorMode
	FEditorModeRegistry::Get().RegisterMode<FBionicApeEditorEdMode>(
		FBionicApeEditorEdMode::EM_BionicApeEditorEdModeId,
		NSLOCTEXT("EditorModes", "BionicApeEditorEdMode", "BionicApe"),
		FSlateIcon(FBionicApeEditorStyle::GetStyleSetName(), "BionicApeEditor.TabIcon", "BionicApeEditor.TabIcon.Small"),
		true/*,
		300*/
		);
	//End EditorMode
	FBAMainMenuSystem::Register();
	
	FBionicApeEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction
	(
		FBionicApeEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateStatic(&FBAMainMenuSystem::Launch)
	);
}
void FBionicApeEditorModule::ShutdownModule()
{
	FBAMainMenuSystem::Unregister();
	FEditorModeRegistry::Get().UnregisterMode(FBionicApeEditorEdMode::EM_BionicApeEditorEdModeId);
	FBionicApeEditorStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBionicApeEditorModule, BionicApeEditor)
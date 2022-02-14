// Created by Bionic Ape. All Rights Reserved.

#include "BAMainMenuSystem/BAMainMenuSystem.h"
#include "BAMainMenuSystem/BAMainMenuSystemCommands.h"
#include "BAMainMenuSystem/SBionicApeEditorMenu.h"

#include "BionicApeEditorStyle.h"

#include "Framework/Docking/TabManager.h"
#include "Framework/Commands/UICommandList.h"

#include "ToolMenus.h"
#include "ToolMenu.h"
#include "ToolMenuEntry.h"

#include "Framework/Commands/UIAction.h"
#include "WorkspaceMenuStructureModule.h"
#include "WorkspaceMenuStructure.h"


#define LOCTEXT_NAMESPACE "MainMenuSystem"

namespace BAMainMenu
{
	const FName BAMainMenuSystemWindowID = FName(TEXT("BAMainMenuSystem"));

	TSharedRef<class SDockTab> SpawnNomadTab(const FSpawnTabArgs& Args)
	{
		return SNew(SDockTab)
			.TabRole(NomadTab)
			[
				SNew(SBionicApeEditorMenu)
			];
	}
}

void FBAMainMenuSystem::Register()
{
	//FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
	//	BAMainMenu::BAMainMenuSystemWindowID,
	//	FOnSpawnTab::CreateStatic(&BAMainMenu::SpawnNomadTab))
	//		.SetDisplayName(LOCTEXT("TabTitle", "Bionic Ape Editor Tools"))
	//		.SetTooltipText(LOCTEXT("TooltipText", "Access all Bionic Ape Editor Tools"))
	//		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
	//		.SetIcon(FSlateIcon(FBionicApeEditorStyle::GetStyleSetName(),
	//	"BionicApeEditor.Image")
	//);

	//UToolMenu* AssetsToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.AssetsToolBar");
	//if (AssetsToolBar)
	//{
	//	FToolMenuSection& Section = AssetsToolBar->AddSection("Content");
	//	FToolMenuEntry ToolMenuEntry = FToolMenuEntry::InitToolBarButton(
	//		"BionicApeEditorLaunchPad",
	//		FUIAction(FExecuteAction::CreateStatic(&FBAMainMenuSystem::Launch)),
	//		LOCTEXT("BAToolbarButtonText_1", "Bionic Ape"),
	//		LOCTEXT("BAToolbarButtonTooltip", "Bionic Ape Editor Tools"),
	//		FSlateIcon(FBionicApeEditorStyle::GetStyleSetName(), TEXT("BionicApeEditor.Image")));
	//	ToolMenuEntry.StyleNameOverride = "CalloutToolbar";
	//	Section.AddEntry(ToolMenuEntry);
	//}
}

void FBAMainMenuSystem::Unregister()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BAMainMenu::BAMainMenuSystemWindowID);
}

void FBAMainMenuSystem::Launch()
{
	FGlobalTabmanager::Get()->TryInvokeTab(BAMainMenu::BAMainMenuSystemWindowID);
}

#undef LOCTEXT_NAMESPACE

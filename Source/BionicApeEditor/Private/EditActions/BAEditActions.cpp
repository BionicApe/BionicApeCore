// Created by Bionic Ape. All Rights Reserved.



#include "EditActions/BAEditActions.h"
#include "EditActions/BAEditActionsCommands.h"

#include "EditActions/BAEditAction_MeshFromBlueprint.h"
#include "EditActions/BAEditAction_RenameSelectedActors.h"


#include "LevelEditor.h"

#include "ToolMenu.h"
#include "ToolMenus.h"
#include "BAEditAction_ActorsFromSelection.h"
#include "BAEditAction_CountSelectedActors.h"
#include "BAEditAction_ForceMobility.h"
#include "BAEditAction_HasConstructorComponents.h"
#include "BAEditAction_MoveActorsToLevelFolder.h"
#include "BionicApeEditorStyle.h"
#include "BAEditAction_ForceDefaultMaterial.h"
#include "BAEditAction_DeleteNullMeshComp.h"
#include "BAEditAction_SelectAllSameMesh.h"

#define LOCTEXT_NAMESPACE "FBAEditActions"

void FBAEditActions::Register()
{
	FBAEditActionsCommands::Register();
	
	CommandList = MakeShareable(new FUICommandList);

	CommandList->MapAction(
		FBAEditActionsCommands::Get().ExtractStaticMesh,
		FExecuteAction::CreateStatic(&FBAEditAction_MeshFromBlueprint::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().ActorsFromSelection,
		FExecuteAction::CreateStatic(&FBAEditAction_ActorsFromSelection::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().RenameSelectedActors,
		FExecuteAction::CreateStatic(&FBAEditAction_RenameSelectedActors::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().CountSelectedActors,
		FExecuteAction::CreateStatic(&FBAEditAction_CountSelectedActors::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().ForceMobility,
		FExecuteAction::CreateStatic(&FBAEditAction_ForceMobility::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().DeleteNullMeshComp,
		FExecuteAction::CreateStatic(&FBAEditAction_DeleteNullMeshComp::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().ForceDefaultMaterial,
		FExecuteAction::CreateStatic(&FBAEditAction_ForceDefaultMaterial::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().HasConstructorComponents,
		FExecuteAction::CreateStatic(&FBAEditAction_HasConstructorComponents::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().MoveActorsToLevelFolder,
		FExecuteAction::CreateStatic(&FBAEditAction_MoveActorsToLevelFolder::ExecuteAction),
		FCanExecuteAction()
	);
	CommandList->MapAction(
		FBAEditActionsCommands::Get().SelectAllSameMesh,
		FExecuteAction::CreateStatic(&FBAEditAction_SelectAllSameMesh::ExecuteAction),
		FCanExecuteAction()
	);

	//CreateButtonInContentBar();
	ExtendEditMenu();
}

void FBAEditActions::ExtendEditMenu()
{
	MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuExtension(
		"EditMain",
		EExtensionHook::After,
		CommandList.ToSharedRef(),
		FMenuExtensionDelegate::CreateLambda(
			[this](FMenuBuilder& MenuBuilder)
			{
				FSlateIcon MenuIcon = FSlateIcon(FBionicApeEditorStyle::GetStyleSetName(), "BionicApeEditor.Image");
				MenuBuilder.AddSubMenu(
					LOCTEXT("BAEditActions", "BAEditActions"),
					LOCTEXT("BAEditActions", "BAEditActions"),
					FNewMenuDelegate::CreateLambda(
						[this](class FMenuBuilder& MenuBuilder)
						{
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().ExtractStaticMesh);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().RenameSelectedActors);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().ActorsFromSelection);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().CountSelectedActors);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().ForceMobility);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().ForceDefaultMaterial);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().DeleteNullMeshComp);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().HasConstructorComponents);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().MoveActorsToLevelFolder);
							MenuBuilder.AddMenuEntry(FBAEditActionsCommands::Get().SelectAllSameMesh);
						}
					),
					false,
					MenuIcon
				);
			}
		)
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

}

void FBAEditActions::CreateButtonInContentBar()
{
	UToolMenu* AssetsToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.AssetsToolBar");
	if (AssetsToolBar)
	{
		FToolMenuEntry ToolMenuEntry = FToolMenuEntry::InitToolBarButton(
			"BAEditActions",
			FUIAction(
				FExecuteAction::CreateLambda(
					[]()
					{
						
					}
				)
			),
			LOCTEXT("BAEditActions_Friendly", "BAEditActions"),
			LOCTEXT("BAEditActions_Tooltip", "BAEditActions"),
			FSlateIcon(FBionicApeEditorStyle::GetStyleSetName(), TEXT("BionicApeEditor.Image")));
		//ToolMenuEntry.StyleNameOverride = "CalloutToolbar";

		FToolMenuSection& Section = AssetsToolBar->AddSection("Content");
		Section.AddEntry(ToolMenuEntry);
	}
}

void FBAEditActions::Unregister()
{
	FBAEditActionsCommands::Unregister();
}

void FBAEditActions::ExtractStaticMesh()
{

}
#undef LOCTEXT_NAMESPACE
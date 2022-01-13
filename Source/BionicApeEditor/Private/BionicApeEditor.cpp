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

#include "BaseEditorTool.h"
#include "Widgets/SWindow.h"
#include "BaseEditorToolCustomization.h"
#include "EditActions/BAEditActions.h"


static const FName BionicApeEditorTabName("BionicApeEditorTab");

#define LOCTEXT_NAMESPACE "BionicApeEditorModule"

class FBionicApeEditorModule : public IBionicApeEditorModule
{

protected:

	TSharedPtr<class FUICommandList> PluginCommands;

	FBAEditActions BAEditActions;

public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	//From Unreal Video
	static void AddMenuCommands(FMenuBuilder& MenuBuilder);
	static void AddToolbarCommands(FToolBarBuilder& ToolbarBuilder);
	static void CreateToolListMenu(class FMenuBuilder& MenuBuilder);
	static void TriggerTool(UClass* ToolClass);
	static void OnToolWindowClosed(const TSharedRef<SWindow>& WindowBeingClosed, TWeakObjectPtr<UBaseEditorTool> ToolInstance);
	//End From Unreal Video
};

void FBionicApeEditorModule::StartupModule()
{

	//Custom Class Layout
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout("BaseEditorTool", FOnGetDetailCustomizationInstance::CreateStatic(&FBaseEditorToolCustomization::MakeInstance));
		PropertyModule.NotifyCustomizationModuleChanged();
	}

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
	FBionicApeEditorCommands::Register();
	
	FBAMainMenuSystem::Register();
	BAEditActions.Register();


	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction
	(
		FBionicApeEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateStatic(&FBAMainMenuSystem::Launch)
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));

	//From Unreal Video
	TSharedRef<FExtender> MenuExtender(new FExtender());
	MenuExtender->AddMenuExtension(
		"EditMain",
		EExtensionHook::After,
		PluginCommands.ToSharedRef(),
		FMenuExtensionDelegate::CreateStatic(&FBionicApeEditorModule::AddMenuCommands));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	//End From Unreal Video


}


void FBionicApeEditorModule::AddToolbarCommands(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.AddToolBarButton(FBionicApeEditorCommands::Get().OpenPluginWindow);
}

void FBionicApeEditorModule::AddMenuCommands(FMenuBuilder& MenuBuilder)
{
	FSlateIcon DocMenuIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.BrowseDocumentation");
	MenuBuilder.AddSubMenu(
		LOCTEXT("BionicApeTools", "Bionic Ape Tools"),
		LOCTEXT("BionicApeTools", "Bionic Ape Tools"),
		FNewMenuDelegate::CreateStatic(&FBionicApeEditorModule::CreateToolListMenu),
		false,
		DocMenuIcon
	);
}

void FBionicApeEditorModule::ShutdownModule()
{
	FBAMainMenuSystem::Unregister();
	FEditorModeRegistry::Get().UnregisterMode(FBionicApeEditorEdMode::EM_BionicApeEditorEdModeId);
	FBionicApeEditorStyle::Shutdown();
}

void FBionicApeEditorModule::CreateToolListMenu(class FMenuBuilder& MenuBuilder)
{
	FSlateIcon DocItemIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.BrowseDocumentation");

	//Add to ToolListMenu
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* Class = *ClassIt;

		if (!Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Abstract))
		{
			if (Class->IsChildOf(UBaseEditorTool::StaticClass()))
			{
				FString FriendlyName = Class->GetName();
				FText MenuDescription = FText::Format(LOCTEXT("ToolMenuDescription", "{0}"), FText::FromString(FriendlyName));
				FText MenuTooltip = FText::Format(LOCTEXT("ToolMenuTooltip", "Execute the {0} Tool"), FText::FromString(FriendlyName));

				FUIAction Action(FExecuteAction::CreateStatic(&FBionicApeEditorModule::TriggerTool, Class));

				MenuBuilder.AddMenuEntry(
					MenuDescription,
					MenuTooltip,
					FSlateIcon(),
					Action
				);
			}
		}
	}
}

void FBionicApeEditorModule::TriggerTool(UClass* ToolClass)
{
	UBaseEditorTool* ToolInstance = NewObject<UBaseEditorTool>(GetTransientPackage(), ToolClass);
	ToolInstance->AddToRoot();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	TArray<UObject*> ObjectsToView;
	ObjectsToView.Add(ToolInstance);
	TSharedRef<SWindow> Window = PropertyModule.CreateFloatingDetailsView(ObjectsToView, /*bIsLocakble =*/false);

	Window->SetOnWindowClosed(FOnWindowClosed::CreateStatic(&FBionicApeEditorModule::OnToolWindowClosed, TWeakObjectPtr<UBaseEditorTool>(ToolInstance)));
}


void FBionicApeEditorModule::OnToolWindowClosed(const TSharedRef<SWindow>& WindowBeingClosed, TWeakObjectPtr<UBaseEditorTool> ToolInstance)
{
	ToolInstance->RemoveFromRoot();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBionicApeEditorModule, BionicApeEditor)
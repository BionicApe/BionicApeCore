// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMenuBuilder;
class FToolBarBuilder;

class FBionicApeEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	//From Unreal Video
	static void AddMenuCommands(FMenuBuilder& MenuBuilder);
	static void AddToolbarCommands(FToolBarBuilder& ToolbarBuilder);
	static void CreateToolListMenu(class FMenuBuilder& MenuBuilder);
	static void TriggerTool(UClass* ToolClass);
	static void OnToolWindowClosed(const TSharedRef<SWindow>& WindowBeingClosed, TWeakObjectPtr<UBaseEditorTool> ToolInstance);

	//End From Unreal Video

	TSharedPtr<class FUICommandList> PluginCommands;
};

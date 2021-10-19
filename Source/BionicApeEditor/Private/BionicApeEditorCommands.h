// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BionicApeEditorStyle.h"
/**
 *
 */
class FBionicApeEditorCommands : public TCommands<FBionicApeEditorCommands>
{
public:
	FBionicApeEditorCommands() :
		TCommands<FBionicApeEditorCommands>(
			TEXT("BionicApeEditor"), //Context name for fast lookup
			NSLOCTEXT("Contexts", "BionicApeEditor", "BionicApe Editor"), //Localized context name for displaying
			NAME_None, // Parent
			FBionicApeEditorStyle::GetStyleSetName()// Icon Style Set
			)
	{
	}

	virtual void RegisterCommands() override;

	//TSharedPtr<FUICommandInfo> OpenModuleGeneratorTool;

	//TSharedPtr<FUICommandInfo> NewModule;

	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};

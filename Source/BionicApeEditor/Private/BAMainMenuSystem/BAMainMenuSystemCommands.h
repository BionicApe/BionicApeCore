// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BionicApeEditorStyle.h"
#include "Framework/Commands/UICommandList.h"
/**
 *
 */
class FBAMainMenuSystemCommands : public TCommands<FBAMainMenuSystemCommands>
{
public:
	FBAMainMenuSystemCommands()
		: TCommands<FBAMainMenuSystemCommands>(
			TEXT("BionicApeEditor"), //Context name for fast lookup
			NSLOCTEXT("Contexts", "BionicApeEditor", "BionicApe Editor"), //Localized context name for displaying
			NAME_None, // Parent
			FBionicApeEditorStyle::GetStyleSetName()// Icon Style Set
			)//
	{
	}

	//TCommand interface
	virtual void RegisterCommands() override;
	//End TCommand interface

	TSharedPtr<FUICommandInfo> OpenModuleGeneratorTool;

	TSharedPtr<FUICommandInfo> NewModule;

	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};

// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PltSimEditorStyle.h"
#include "Tools/InteractiveToolsCommands.h"

class FBAEditActionsCommands : public TCommands<FBAEditActionsCommands>
{
public:

	FBAEditActionsCommands()
		: TCommands<FBAEditActionsCommands>(TEXT("BAEditActions"), NSLOCTEXT("Contexts", "BAEditActions", "BAEditActions"), NAME_None, FPltSimEditorStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:

	TSharedPtr<FUICommandInfo> ExtractStaticMesh;
	TSharedPtr<FUICommandInfo> ActorsFromSelection;
	TSharedPtr<FUICommandInfo> RenameSelectedActors;
	TSharedPtr<FUICommandInfo> CountSelectedActors;
};
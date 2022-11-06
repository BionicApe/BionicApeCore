// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BionicApeEditorStyle.h"
#include "Tools/InteractiveToolsCommands.h"

class FBAEditActionsCommands : public TCommands<FBAEditActionsCommands>
{
public:

	FBAEditActionsCommands()
		: TCommands<FBAEditActionsCommands>(TEXT("BAEditActions"), NSLOCTEXT("Contexts", "BAEditActions", "BAEditActions"), NAME_None, FBionicApeEditorStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:

	TSharedPtr<FUICommandInfo> ExtractStaticMesh;
	TSharedPtr<FUICommandInfo> ActorsFromSelection;
	TSharedPtr<FUICommandInfo> RenameSelectedActors;
	TSharedPtr<FUICommandInfo> CountSelectedActors;
	TSharedPtr<FUICommandInfo> ForceMobility;
	TSharedPtr<FUICommandInfo> ForceDefaultMaterial;
	TSharedPtr<FUICommandInfo> DeleteNullMeshComp;
	TSharedPtr<FUICommandInfo> HasConstructorComponents;
	TSharedPtr<FUICommandInfo> MoveActorsToLevelFolder;
	TSharedPtr<FUICommandInfo> SelectAllSameMesh;	
	TSharedPtr<FUICommandInfo> CreateFactory;
};
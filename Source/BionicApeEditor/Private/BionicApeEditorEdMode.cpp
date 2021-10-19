// Created by Bionic Ape. All Rights Reserved.

#include "BionicApeEditorEdMode.h"
#include "BionicApeEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FBionicApeEditorEdMode::EM_BionicApeEditorEdModeId = TEXT("EM_BionicApeEditorEdMode");

FBionicApeEditorEdMode::FBionicApeEditorEdMode()
{

}

FBionicApeEditorEdMode::~FBionicApeEditorEdMode()
{

}

void FBionicApeEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FBionicApeEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FBionicApeEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FBionicApeEditorEdMode::UsesToolkits() const
{
	return true;
}





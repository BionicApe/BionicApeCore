// Created by Bionic Ape. All Rights Reserved.

#include "BAEditAction_CreateFactory.h"

#include "EngineUtils.h"

#include "UObject/NoExportTypes.h"

#include "Kismet2/SClassPickerDialog.h"
#include "Editor/EditorEngine.h"
#include "Editor.h"

#include "CreateFactoryOptions.h"
#include "CreateFactoryWindow.h"

#define LOCTEXT_NAMESPACE "BAEditAction_CreateFactory"


void FBAEditAction_CreateFactory::ExecuteAction()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("Not valid World"));
		return;
	}

	GEditor->BeginTransaction(LOCTEXT("BACreateAction_CreateFactory", "Create Factory"));

	TSharedRef<SCreateFactoryWindow> OptionsModal = SNew(SCreateFactoryWindow);
	// this blocks until the modal is closed
	FCreateFactoryOptions CreateFactoryOptions;
	bool bAccepted = OptionsModal->ShowModal(CreateFactoryOptions);

	if (!bAccepted)
	{
		return;
	}
	
	GEditor->EndTransaction();
}


#undef LOCTEXT_NAMESPACE
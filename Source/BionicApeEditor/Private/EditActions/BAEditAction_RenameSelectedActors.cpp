// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_RenameSelectedActors.h"
#include "Dialogs/Dialogs.h"
#include "Engine/Selection.h"
#include "Editor/EditorEngine.h"

#include "Widgets/Input/SEditableText.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "BAEditAction_RenameSelectedActors"


void FBAEditAction_RenameSelectedActors::ExecuteAction()
{

	TSharedRef<SEditableText> EditableText = SNew(SEditableText).Text(FText::FromString("NewName")).IsReadOnly(false);
	
	SGenericDialogWidget::OpenDialog(
		LOCTEXT("FBAEditAction_RenameSelectedActors", "Rename Selected Actors"), 
		EditableText,
		SGenericDialogWidget::FArguments(), 
		true
	);

	GEditor->BeginTransaction(LOCTEXT("BAEditAction_RenameSelectedActors", "Rename Selected Actors"));
	FString NewName = EditableText->GetText().ToString();
	
	USelection* SelectedActors = GEditor->GetSelectedActors();

	// Let editor know that we're about to do something that we want to undo/redo

	// For each selected actor
	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	{
		if (AActor* LevelActor = Cast<AActor>(*Iter))
		{
			//LevelActor->SetActorLabel(*NewName);//Doesn't make it unique so we use FActorLabelUtilities::SetActorLabelUnique
			FActorLabelUtilities::SetActorLabelUnique(LevelActor, NewName);
		}
	}

	// We're done moving actors so close transaction

	GEditor->EndTransaction();
}

#undef LOCTEXT_NAMESPACE
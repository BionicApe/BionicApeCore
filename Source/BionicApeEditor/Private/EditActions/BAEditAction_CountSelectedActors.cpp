// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_CountSelectedActors.h"
#include "Dialogs/Dialogs.h"
#include "Engine/Selection.h"
#include "Editor/EditorEngine.h"

#include "Widgets/Input/SEditableText.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "BAEditAction_CountSelectedActors"


void FBAEditAction_CountSelectedActors::ExecuteAction()
{

	TSharedRef<SEditableText> EditableText = SNew(SEditableText).Text(FText::FromString("NewName")).IsReadOnly(false);
	
	SGenericDialogWidget::OpenDialog(
		LOCTEXT("FBAEditAction_CountSelectedActors", "Count Selected Actors"), 
		EditableText,
		SGenericDialogWidget::FArguments(), 
		true
	);

	USelection* SelectedActors = GEditor->GetSelectedActors();

	FMessageDialog::Open(
		EAppMsgType::YesNo,
		FText::Format(LOCTEXT("ActorsCount", "Selected Actors: '{0}'"), FText::AsNumber(SelectedActors->Num()))
	);	
}

#undef LOCTEXT_NAMESPACE
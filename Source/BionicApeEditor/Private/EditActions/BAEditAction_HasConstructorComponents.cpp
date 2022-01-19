// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_HasConstructorComponents.h"
#include "Dialogs/Dialogs.h"
#include "Engine/Selection.h"
#include "Editor/EditorEngine.h"

#include "Widgets/Input/SEditableText.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "BAEditAction_HasConstructorComponents"


void FBAEditAction_HasConstructorComponents::ExecuteAction()
{
	USelection* SelectedActors = GEditor->GetSelectedActors();

	TSet<UClass*> ClassesAlreadySeen;

	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	{
		if (AActor* Actor = Cast<AActor>(*Iter))
		{
			if (ClassesAlreadySeen.Contains(Actor->GetClass()))
			{
				continue;
			}

			if (FBAEditActionsLib::HasConstructorComponents(Actor))
			{
				ClassesAlreadySeen.Add(Actor->GetClass());

				FMessageDialog::Open(
					EAppMsgType::Ok,
					FText::Format(LOCTEXT("ConstructedComponent", "The Actor {0} has constructed Components (Skiping actors of the same class)"), FText::FromString(Actor->GetActorLabel()))
				);

			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
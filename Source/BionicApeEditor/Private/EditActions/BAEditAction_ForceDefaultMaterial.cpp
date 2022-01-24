// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_ForceDefaultMaterial.h"
#include "Dialogs/Dialogs.h"
#include "Engine/Selection.h"
#include "Editor/EditorEngine.h"

#include "Widgets/Input/SEditableText.h"
#include "Editor.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectGlobals.h"

#define LOCTEXT_NAMESPACE "BAEditAction_ForceDefaultMaterial"


void FBAEditAction_ForceDefaultMaterial::ExecuteAction()
{

	UMaterialInterface* DefaultMaterial = FindObject<UMaterialInterface>(ANY_PACKAGE, TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));

	if (!DefaultMaterial)
	{
		FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("DeleteOriginal", "Fail to load 'WorldGridMaterial' asset"));
		return;
	}

	USelection* SelectedActors = GEditor->GetSelectedActors();

	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	{
		if (AActor* Actor = Cast<AActor>(*Iter))
		{
			for (UActorComponent* Comp : Actor->GetComponents())
			{
				if (UMeshComponent* MeshComp = Cast<UMeshComponent>(Comp))
				{
					for (int32 i = 0; i < MeshComp->GetNumMaterials(); i++)
					{
						MeshComp->SetMaterial(i, DefaultMaterial);
					}
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
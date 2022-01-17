// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_ActorsFromSelection.h"

#include "EngineUtils.h"

#include "UObject/NoExportTypes.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"

#include "Kismet2/SClassPickerDialog.h"

#include "Misc/MessageDialog.h"

#include "Camera/CameraActor.h"

#include "Components/PointLightComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/RectLightComponent.h"

#include "Engine/DirectionalLight.h"
#include "Engine/Light.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/PointLight.h"
#include "Engine/RectLight.h"
#include "Engine/ReflectionCapture.h"
#include "Engine/SpotLight.h"
#include "Engine/StaticMeshActor.h"

#include "Editor/EditorEngine.h"
#include "Editor.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Selection.h"
#include "BAEditActionsLib.h"


#define LOCTEXT_NAMESPACE "BAEditAction_ActorsFromSelection"


void FBAEditAction_ActorsFromSelection::ExecuteAction()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("Not valid World"));
		return;
	}

	GEditor->BeginTransaction(LOCTEXT("BAEditAction_ActorsFromSelection", "Create Mesh Actors from Actor Class"));

	bool const bDeleteOriginal = EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("DeleteOriginal", "Do you want to delete original Actor?"));
	bool const bSpawnOneActorPerComponent = EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("SpawnOneActorPerComponent ", "Do you want to Spawn one Actor per Component?"));

	USelection* SelectedActors = GEditor->GetSelectedActors();

	// Let editor know that we're about to do something that we want to undo/redo

	// For each selected actor
	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	{
		AActor* Actor = Cast<AActor>(*Iter);
		if (!Actor)
		{
			continue;
		}

		FBAEditActionsLib::SpawnActorsFromComponents(Actor, World, Actor->GetClass(), bSpawnOneActorPerComponent);

		if (bDeleteOriginal)
		{
			Actor->Destroy();
		}
	}

	GEditor->EndTransaction();
}

#undef LOCTEXT_NAMESPACE
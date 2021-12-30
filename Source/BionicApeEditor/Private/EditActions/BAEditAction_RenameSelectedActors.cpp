// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_RenameSelectedActors.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"

#include "Kismet2/SClassPickerDialog.h"

#include "EngineUtils.h"

#include "Engine/StaticMeshActor.h"
#include "BAEditorStatics.h"

class FAssetClassParentFilter : public IClassViewerFilter
{
public:
	/** All children of these classes will be included unless filtered out by another setting. */
	TSet< const UClass* > AllowedChildrenOfClasses;

	/** Disallowed class flags. */
	EClassFlags DisallowedClassFlags;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InClass->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

#define LOCTEXT_NAMESPACE "BAEditAction_RenameSelectedActors"


void FBAEditAction_RenameSelectedActors::ExecuteAction()
{
	UWorld* World = UBAEditorStatics::GetEditorMainWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("Not valid World"));
		return;
	}

	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

	TSharedPtr<FAssetClassParentFilter> Filter = MakeShared<FAssetClassParentFilter>();
	Filter->AllowedChildrenOfClasses.Add(AActor::StaticClass());

	Options.ClassFilter = Filter;

	const FText TitleText = NSLOCTEXT("AudioModulation", "CreateSoundModulationParameterOptions", "Select Parameter Class");
	UClass* ChosenClass = nullptr;

	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, AActor::StaticClass());



	if (bPressedOk)
	{
		GEditor->BeginTransaction(LOCTEXT("BAEditAction_RenameSelectedActors", "Create Mesh Actors from Actor Class"));
		for (TActorIterator<AActor> It(World, ChosenClass); It; ++It)
		{
			AActor* Actor = *It;
			if (Actor)
			{
				for (UActorComponent* Comp : Actor->GetComponents())
				{
					AActor* CreatedActor = nullptr;
					
					if (UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(Comp))
					{
						if (StaticMeshComp->GetStaticMesh())
						{
							AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), StaticMeshComp->GetComponentTransform());
							CreatedActor = MeshActor;
							MeshActor->GetStaticMeshComponent()->SetStaticMesh(StaticMeshComp->GetStaticMesh());
						}
					}
					else if (ULightComponent* LightComp = Cast<ULightComponent>(Comp))
					{
						
					}
					
					if (CreatedActor)
					{
						CreatedActor->SetFolderPath(Actor->StaticClass()->GetFName());
					}
				}
			}
		}
		GEditor->EndTransaction();
	}
	
}

#undef LOCTEXT_NAMESPACE
// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_MeshFromBlueprint.h"

#include "EngineUtils.h"

#include "UObject/NoExportTypes.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"

#include "Kismet2/SClassPickerDialog.h"

#include "Misc/MessageDialog.h"

#include "Camera/CameraActor.h"

#include "Engine/Light.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/ReflectionCapture.h"
#include "Engine/StaticMeshActor.h"

#include "Editor/EditorEngine.h"
#include "Editor.h"
#include "BAEditActionsLib.h"

const TSet<FString> FBAEditAction_MeshFromBlueprint::IgnoreClassNames =
{
	"TextRenderActor",
	"WorldSettings",
	"SkeletalMeshActor",
	"Brush",
	"DefaultPhysicsVolume",
	"GameplayDebuggerPlayerManager",
	"AbstractNavData",
	"InstancedFoliageActor",
	"LandscapeGizmoActiveActor",
	"Landscape",
	"BP_Splines_C",
	"DecalActor",
	"LightmassImportanceVolume",
	"AtmosphericFog",
	"BP_Sky_Sphere_C",
	"SkyLight",
	"BASpawnerActor",
	"Emitter",
	"GroupActor",
	"ExponentialHeightFog",
	"PostProcessVolume",

};

const TSet<UClass*> FBAEditAction_MeshFromBlueprint::IgnoreClasses =
{
	AStaticMeshActor::StaticClass(),
	ALight::StaticClass(),
	ACameraActor::StaticClass(),
	AReflectionCapture::StaticClass(),
	ALevelScriptActor::StaticClass()
};

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

#define LOCTEXT_NAMESPACE "BAEditAction_MeshFromBlueprint"


void FBAEditAction_MeshFromBlueprint::ExecuteAction()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("Not valid World"));
		return;
	}

	GEditor->BeginTransaction(LOCTEXT("BAEditAction_MeshFromBlueprint", "Create Mesh Actors from Actor Class"));
	
	bool const bSpawnOneActorPerComponent = EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("SpawnOneActorPerComponent ", "Do you want to Spawn one Actor per Component?"));
	bool const bUseLevelNameAsRootFolder = EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("Use Level as Folder ", "Use level name as Root Folder?"));
	bool const bIterateAllActors = EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("IterateAllActors", "Do you want to iterate all actors?"));


	if (bIterateAllActors)
	{
		TSet<UClass*> ClassesAlreadySeen;
		TSet<AActor*> ActorsToDestroy;

		for (TActorIterator<AActor> It(World, AActor::StaticClass()); It; ++It)
		{
			AActor* Actor = *It;
			{
				if (!Actor)
				{
					continue;
				}
				if (FBAEditAction_MeshFromBlueprint::IgnoreActor(Actor))
				{
					continue;
				}
				bool bIsAlreadyInSet = false;
				ClassesAlreadySeen.Add(Actor->GetClass(), &bIsAlreadyInSet);
				if (bIsAlreadyInSet) continue;
			}

			FName const ClassName = Actor->GetClass()->GetFName();
			bool const bExtractThisClass = EAppReturnType::Type::Yes == FMessageDialog::Open(
				EAppMsgType::YesNo,
				FText::Format(LOCTEXT("LoadingClass", "Replace Actors of class: '{0}'"), FText::FromName(ClassName))
			);

			if (bExtractThisClass)
			{
				bool const bDeleteOriginal = EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("DeleteOriginal", "Do you want to delete original Actor?"));

				for (TActorIterator<AActor> ChosenActorIt(World, Actor->GetClass()); ChosenActorIt; ++ChosenActorIt)
				{
					AActor* ChosenActor = *ChosenActorIt;
					FBAEditActionsLib::SpawnActorsFromComponents(ChosenActor, World, ChosenActor->GetClass(), bSpawnOneActorPerComponent, bUseLevelNameAsRootFolder);
					if (bDeleteOriginal)
					{
						ActorsToDestroy.Add(ChosenActor);
					}
				}
			}
		}
		for (AActor* ActorToDestroy : ActorsToDestroy)
		{
			ActorToDestroy->Destroy();
		}
	}
	else do {

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
			bool const bDeleteOriginal = EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("DeleteOriginal", "Do you want to delete original Actor?"));

			for (TActorIterator<AActor> It(World, ChosenClass); It; ++It)
			{
				AActor* Actor = *It;
				FBAEditActionsLib::SpawnActorsFromComponents(Actor, World, ChosenClass, bSpawnOneActorPerComponent, bUseLevelNameAsRootFolder);

				if (bDeleteOriginal)
				{
					Actor->Destroy();
				}
			}
		}
	} while (EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("Continue_Extracting", "Do you want to continue Extracting?")));

	GEditor->EndTransaction();
}


bool FBAEditAction_MeshFromBlueprint::IgnoreActor(AActor* Actor)
{
	if (IgnoreClassNames.Contains(Actor->GetClass()->GetName()))
	{
		return true;
	}
	for (UClass* Class : IgnoreClasses)
	{
		if (Actor->IsA(Class))
		{
			return true;
		}
	}
	return false;
}


#undef LOCTEXT_NAMESPACE
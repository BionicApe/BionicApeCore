// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/BAEditAction_MeshFromBlueprint.h"

#include "EngineUtils.h"

#include "UObject/NoExportTypes.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"

#include "Kismet2/SClassPickerDialog.h"

#include "BAEditorStatics.h"

#include "Misc/MessageDialog.h"

#include "Components/PointLightComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/RectLightComponent.h"

#include "Engine/DirectionalLight.h"
#include "Engine/Light.h"
#include "Engine/PointLight.h"
#include "Engine/RectLight.h"
#include "Engine/ReflectionCapture.h"
#include "Engine/SpotLight.h"
#include "Engine/StaticMeshActor.h"

#include "Editor/EditorEngine.h"

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
	"BASpawnerActor"
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
	UWorld* World = UBAEditorStatics::GetEditorMainWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("Not valid World"));
		return;
	}

	GEditor->BeginTransaction(LOCTEXT("BAEditAction_MeshFromBlueprint", "Create Mesh Actors from Actor Class"));

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
					FBAEditAction_MeshFromBlueprint::SpawnActorsFromComponents(ChosenActor, World, ChosenActor->GetClass());
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
				FBAEditAction_MeshFromBlueprint::SpawnActorsFromComponents(Actor, World, ChosenClass);

				if (bDeleteOriginal)
				{
					Actor->Destroy();
				}
			}
		}
	} while (EAppReturnType::Type::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("Continue_Extracting", "Do you want to continue Extracting?")));

	GEditor->EndTransaction();
}



void FBAEditAction_MeshFromBlueprint::SpawnActorsFromComponents(AActor* Actor, UWorld* World, UClass* ChosenClass)
{
	if (Actor)
	{
		for (UActorComponent* Comp : Actor->GetComponents())
		{
			if (UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(Comp))
			{
				if (UStaticMesh* StaticMesh = StaticMeshComp->GetStaticMesh())
				{
					AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), StaticMeshComp->GetComponentTransform());
					MeshActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
					MeshActor->SetFolderPath(ChosenClass->GetFName());
					FActorLabelUtilities::SetActorLabelUnique(MeshActor, StaticMesh->GetName());

					for (int32 i = 0; i < StaticMeshComp->GetNumMaterials(); i++)
					{
						if (UMaterialInterface* Material = StaticMeshComp->GetMaterial(i))
						{
							if (!Material->IsA<UMaterialInstanceDynamic>())//We don't set the MID since we don't know their origin
							{
								MeshActor->GetStaticMeshComponent()->SetMaterial(i, Material);
							}
						}
					}
				}
			}
			else if (ULightComponent* LightComp = Cast<ULightComponent>(Comp))
			{
				ALight* LightActor = nullptr;

				if (LightComp->IsA<UDirectionalLightComponent>())
				{
					LightActor = World->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), LightComp->GetComponentTransform());
				}
				else if (LightComp->IsA<USpotLightComponent>())//WARNING: USpotLightComponent is a subclass of UPointLightComponent, so it must be tested first
				{
					LightActor = World->SpawnActor<ASpotLight>(ASpotLight::StaticClass(), LightComp->GetComponentTransform());

					USpotLightComponent* SpotLightComponent = Cast<USpotLightComponent>(LightActor->GetLightComponent());
					USpotLightComponent* OriginSpotLightComp = Cast<USpotLightComponent>(LightComp);
					SpotLightComponent->SetAttenuationRadius(OriginSpotLightComp->AttenuationRadius);
					SpotLightComponent->SetInnerConeAngle(OriginSpotLightComp->InnerConeAngle);
					SpotLightComponent->SetOuterConeAngle(OriginSpotLightComp->OuterConeAngle);
					SpotLightComponent->SetIntensityUnits(OriginSpotLightComp->IntensityUnits);

				}
				else if (LightComp->IsA<UPointLightComponent>())
				{
					LightActor = World->SpawnActor<APointLight>(APointLight::StaticClass(), LightComp->GetComponentTransform());

					UPointLightComponent* PointLightComponent = Cast<UPointLightComponent>(LightActor->GetLightComponent());
					UPointLightComponent* OriginPointLightComp = Cast<UPointLightComponent>(LightComp);
					PointLightComponent->SetAttenuationRadius(OriginPointLightComp->AttenuationRadius);
					PointLightComponent->SetIntensityUnits(OriginPointLightComp->IntensityUnits);

				}
				else if (LightComp->IsA<URectLightComponent>())
				{
					LightActor = World->SpawnActor<ARectLight>(ARectLight::StaticClass(), LightComp->GetComponentTransform());
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Class not found for light component"));
					continue;
				}

				ULightComponent* NewLightComponent = LightActor->GetLightComponent();
				NewLightComponent->SetIntensity(LightComp->Intensity);
				NewLightComponent->SetLightColor(LightComp->GetLightColor());


				//TODO: IMPORTANT, if we get this working we don't need the above
				//StaticDuplicateObject() is for duplicating the objects.
				//UEngine::FCopyPropertiesForUnrelatedObjectsParams CopyParams;
				//CopyParams.bNotifyObjectReplacement = false;
				//CopyParams.bPreserveRootComponent = false;
				//UEngine::CopyPropertiesForUnrelatedObjects(LightComp, LightActor->GetLightComponent(), CopyParams);

				//Todo: this doesn't work, it should work, but it doesn't. So That's why we copy the most representative values.
				//for (TFieldIterator<FProperty> PropIt(LightComp->StaticClass()); PropIt; ++PropIt)
				//{
				//	FProperty* Property = *PropIt;

				//	if (!Property->IsA<FObjectProperty>())
				//	{
				//		EditorUtilities::CopySingleProperty(LightComp, LightActor->GetLightComponent(), Property);
				//	}
				//}
				//End Important TODO
			}
		}
	}
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
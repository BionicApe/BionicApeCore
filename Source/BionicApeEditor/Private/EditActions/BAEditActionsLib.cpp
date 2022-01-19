// Created by Bionic Ape. All Rights Reserved.


#include "EditActions/BAEditActionsLib.h"


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


#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/UObjectGlobals.h"

#include "GameFramework/Actor.h"



FName FBAEditActionsLib::CreateFolderPath(AActor* Actor, UClass* ChosenClass, bool const bUseLevelNameAsRootFolder /*= true*/)
{
	return bUseLevelNameAsRootFolder ? *FString::Printf(TEXT("%s/%s"), *Actor->GetLevel()->GetOuter()->GetName(), *ChosenClass->GetName()) : *ChosenClass->GetName();
}

bool FBAEditActionsLib::HasConstructorComponents(AActor* Actor)
{
	for (UActorComponent* Comp : Actor->GetComponents())
	{
		if (Comp->CreationMethod == EComponentCreationMethod::UserConstructionScript)
		{
			return true;
		}
	}
	return false;
}

bool FBAEditActionsLib::SpawnActorsFromComponents(AActor* Actor, UWorld* World, UClass* ChosenClass, bool const bSpawnOneActorPerComp, bool const bUseLevelNameAsRootFolder)
{
	if (!Actor || !World || !ChosenClass)
	{
		UE_LOG(LogTemp, Error, TEXT("invalid parameters: !Actor || !World || !ChosenClass"));
		return false;
	}

	AActor* SpawnedActor = nullptr;

	if (!bSpawnOneActorPerComp)
	{
		//Spawn only one Actor
		SpawnedActor = World->SpawnActor<AActor>(AActor::StaticClass(), Actor->GetTransform());
		SpawnedActor->SetFolderPath(FBAEditActionsLib::CreateFolderPath(Actor, ChosenClass, bUseLevelNameAsRootFolder));
		FActorLabelUtilities::SetActorLabelUnique(SpawnedActor, ChosenClass->GetName());

		USceneComponent* RootComponent = Actor->GetRootComponent();
		RootComponent->SetMobility(Actor->GetRootComponent()->Mobility);
	}

	for (UActorComponent* Comp : Actor->GetComponents())
	{
		if (UStaticMeshComponent* OriginalStaticMeshComp = Cast<UStaticMeshComponent>(Comp))
		{
			if (UStaticMesh* StaticMesh = OriginalStaticMeshComp->GetStaticMesh())
			{

				UStaticMeshComponent* CreatedComp = nullptr;

				if (bSpawnOneActorPerComp)
				{

					AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), OriginalStaticMeshComp->GetComponentTransform());
					MeshActor->SetFolderPath(FBAEditActionsLib::CreateFolderPath(Actor, ChosenClass, bUseLevelNameAsRootFolder));
					FActorLabelUtilities::SetActorLabelUnique(MeshActor, StaticMesh->GetName());
					CreatedComp = MeshActor->GetStaticMeshComponent();
				}
				else
				{
					CreatedComp = NewObject<UStaticMeshComponent>(SpawnedActor);
					//CreatedComp->CreationMethod = EComponentCreationMethod::Instance;
					SpawnedActor->AddInstanceComponent(CreatedComp);
					CreatedComp->SetWorldTransform(OriginalStaticMeshComp->GetComponentTransform());
					CreatedComp->AttachToComponent(SpawnedActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					CreatedComp->OnComponentCreated();
					CreatedComp->RegisterComponent();
				}

				CreatedComp->SetStaticMesh(StaticMesh);
				CreatedComp->SetMobility(OriginalStaticMeshComp->Mobility);

				for (int32 i = 0; i < OriginalStaticMeshComp->GetNumMaterials(); i++)
				{
					if (UMaterialInterface* Material = OriginalStaticMeshComp->GetMaterial(i))
					{
						if (!Material->IsA<UMaterialInstanceDynamic>())//We don't set the MID since we don't know their origin
						{
							CreatedComp->SetMaterial(i, Material);
						}
					}
				}
			}
		}
		else if (ULightComponent* OriginalLightComp = Cast<ULightComponent>(Comp))
		{
			ULightComponent* NewLightComponent = nullptr;

			if (bSpawnOneActorPerComp)
			{
				ALight* LightActor = nullptr;

				if (OriginalLightComp->IsA<UDirectionalLightComponent>())
				{
					LightActor = World->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), OriginalLightComp->GetComponentTransform());
				}
				else if (OriginalLightComp->IsA<USpotLightComponent>())//WARNING: USpotLightComponent is a subclass of UPointLightComponent, so it must be tested first
				{
					LightActor = World->SpawnActor<ASpotLight>(ASpotLight::StaticClass(), OriginalLightComp->GetComponentTransform());
				}
				else if (OriginalLightComp->IsA<UPointLightComponent>())
				{
					LightActor = World->SpawnActor<APointLight>(APointLight::StaticClass(), OriginalLightComp->GetComponentTransform());
				}
				else if (OriginalLightComp->IsA<URectLightComponent>())
				{
					LightActor = World->SpawnActor<ARectLight>(ARectLight::StaticClass(), OriginalLightComp->GetComponentTransform());
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Class not found for light component"));
					continue;
				}

				LightActor->SetFolderPath(FBAEditActionsLib::CreateFolderPath(Actor, ChosenClass, bUseLevelNameAsRootFolder));
				FActorLabelUtilities::SetActorLabelUnique(LightActor, ChosenClass->GetName());

				NewLightComponent = LightActor->GetLightComponent();
			}
			else
			{
				NewLightComponent = NewObject<ULightComponent>(SpawnedActor, OriginalLightComp->GetClass());
				//NewLightComponent->CreationMethod = EComponentCreationMethod::Instance;
				SpawnedActor->AddInstanceComponent(NewLightComponent);
				NewLightComponent->SetWorldTransform(OriginalLightComp->GetComponentTransform());
				NewLightComponent->AttachToComponent(SpawnedActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
				NewLightComponent->OnComponentCreated();
				NewLightComponent->RegisterComponent();
			}

			{//Set light values
				NewLightComponent->SetMobility(OriginalLightComp->Mobility);
				NewLightComponent->SetIntensity(OriginalLightComp->Intensity);
				NewLightComponent->SetLightColor(OriginalLightComp->GetLightColor());

				if (OriginalLightComp->IsA<USpotLightComponent>())//WARNING: USpotLightComponent is a subclass of UPointLightComponent, so it must be tested first
				{
					USpotLightComponent* OriginSpotLightComp = Cast<USpotLightComponent>(OriginalLightComp);
					USpotLightComponent* SpotLightComponent = Cast<USpotLightComponent>(NewLightComponent);

					SpotLightComponent->SetAttenuationRadius(OriginSpotLightComp->AttenuationRadius);
					SpotLightComponent->SetInnerConeAngle(OriginSpotLightComp->InnerConeAngle);
					SpotLightComponent->SetOuterConeAngle(OriginSpotLightComp->OuterConeAngle);
					SpotLightComponent->SetIntensityUnits(OriginSpotLightComp->IntensityUnits);
				}
				else if (OriginalLightComp->IsA<UPointLightComponent>())
				{
					UPointLightComponent* PointLightComponent = Cast<UPointLightComponent>(NewLightComponent);
					UPointLightComponent* OriginPointLightComp = Cast<UPointLightComponent>(OriginalLightComp);
					PointLightComponent->SetAttenuationRadius(OriginPointLightComp->AttenuationRadius);
					PointLightComponent->SetIntensityUnits(OriginPointLightComp->IntensityUnits);
				}
			}

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

	return true;
}

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


bool FBAEditActionsLib::SpawnActorsFromComponents(AActor* Actor, UWorld* World, UClass* ChosenClass, bool const bSpawnOneActorPerComp)
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
		SpawnedActor->SetFolderPath(ChosenClass->GetFName());
		FActorLabelUtilities::SetActorLabelUnique(SpawnedActor, ChosenClass->GetName());
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
					MeshActor->SetFolderPath(ChosenClass->GetFName());
					FActorLabelUtilities::SetActorLabelUnique(MeshActor, StaticMesh->GetName());
					CreatedComp = MeshActor->GetStaticMeshComponent();
				}
				else
				{
					CreatedComp = NewObject<UStaticMeshComponent>(SpawnedActor);
					CreatedComp->CreationMethod = EComponentCreationMethod::Instance;
					CreatedComp->SetWorldTransform(OriginalStaticMeshComp->GetComponentTransform());
					CreatedComp->AttachToComponent(SpawnedActor->GetRootComponent(),FAttachmentTransformRules::KeepWorldTransform);
					CreatedComp->RegisterComponent();
				}

				CreatedComp->SetStaticMesh(StaticMesh);


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
		else if (ULightComponent* LightComp = Cast<ULightComponent>(Comp))
		{
			ULightComponent* NewLightComponent = nullptr;

			if (bSpawnOneActorPerComp)
			{
				ALight* LightActor = nullptr;

				if (LightComp->IsA<UDirectionalLightComponent>())
				{
					LightActor = World->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), LightComp->GetComponentTransform());
				}
				else if (LightComp->IsA<USpotLightComponent>())//WARNING: USpotLightComponent is a subclass of UPointLightComponent, so it must be tested first
				{
					LightActor = World->SpawnActor<ASpotLight>(ASpotLight::StaticClass(), LightComp->GetComponentTransform());
				}
				else if (LightComp->IsA<UPointLightComponent>())
				{
					LightActor = World->SpawnActor<APointLight>(APointLight::StaticClass(), LightComp->GetComponentTransform());
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

				LightActor->SetFolderPath(ChosenClass->GetFName());
				FActorLabelUtilities::SetActorLabelUnique(LightActor, ChosenClass->GetName());

				NewLightComponent = LightActor->GetLightComponent();
			}
			else
			{


				NewLightComponent = NewObject<ULightComponent>(SpawnedActor, LightComp->GetClass());
				NewLightComponent->CreationMethod = EComponentCreationMethod::Instance;
				NewLightComponent->SetWorldTransform(LightComp->GetComponentTransform());
				NewLightComponent->AttachToComponent(SpawnedActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
				NewLightComponent->RegisterComponent();
			}

			{//Set light values
				if (LightComp->IsA<USpotLightComponent>())//WARNING: USpotLightComponent is a subclass of UPointLightComponent, so it must be tested first
				{
					USpotLightComponent* OriginSpotLightComp = Cast<USpotLightComponent>(LightComp);
					USpotLightComponent* SpotLightComponent = Cast<USpotLightComponent>(NewLightComponent);

					SpotLightComponent->SetAttenuationRadius(OriginSpotLightComp->AttenuationRadius);
					SpotLightComponent->SetInnerConeAngle(OriginSpotLightComp->InnerConeAngle);
					SpotLightComponent->SetOuterConeAngle(OriginSpotLightComp->OuterConeAngle);
					SpotLightComponent->SetIntensityUnits(OriginSpotLightComp->IntensityUnits);

				}
				else if (LightComp->IsA<UPointLightComponent>())
				{
					UPointLightComponent* PointLightComponent = Cast<UPointLightComponent>(NewLightComponent);
					UPointLightComponent* OriginPointLightComp = Cast<UPointLightComponent>(LightComp);
					PointLightComponent->SetAttenuationRadius(OriginPointLightComp->AttenuationRadius);
					PointLightComponent->SetIntensityUnits(OriginPointLightComp->IntensityUnits);

				}

				NewLightComponent->SetIntensity(LightComp->Intensity);
				NewLightComponent->SetLightColor(LightComp->GetLightColor());
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

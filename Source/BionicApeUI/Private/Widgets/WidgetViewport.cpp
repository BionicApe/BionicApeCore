// Created by Bionic Ape. All rights reseved.


#include "Widgets/WidgetViewport.h"

#include "Animation/SkeletalMeshActor.h"

#include "Camera/CameraComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ReflectionCaptureComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/Viewport.h"

#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkyLight.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"

#include "PreviewScene.h"

#include "Templates/SharedPointer.h"

#include "Slate/SceneViewport.h"

#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SViewport.h"

#include "Engine/World.h"
#include "Helpers/ViewportWidgetHelper.h"

#define LOCTEXT_NAMESPACE "UWidgetViewport"

UWidgetViewport::UWidgetViewport(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
	BackgroundColor = FLinearColor::Gray;
	WidgetWorld = nullptr;
	DirectionalLight = nullptr;
	SkyLight = nullptr;
	bGenerateDefaultLight = true;
	Opacity = 1.0f;
}

#if WITH_EDITOR
const FText UWidgetViewport::GetPaletteCategory()
{
	return LOCTEXT("ExtraRuntime", "ExtraRuntime");
}
#endif

void UWidgetViewport::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
}

void UWidgetViewport::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

TSharedRef<SWidget> UWidgetViewport::RebuildWidget()
{
	if (IsDesignTime())
	{
		TSharedPtr<SHorizontalBox> Box = SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Viewport", "Viewport will be display on instance"))
			];


		return Box->AsShared();
	}

	WidgetWorld = NewObject<UWorld>();
	WidgetWorld->WorldType = EWorldType::GamePreview;
	FWorldContext& WorldContext = GEngine->CreateNewWorldContext(WidgetWorld->WorldType);
	WorldContext.SetCurrentWorld(WidgetWorld);

	TSubclassOf<class AGameModeBase> DefaultGameMode;
	WidgetWorld->InitializeNewWorld(UWorld::InitializationValues()
		.AllowAudioPlayback(false)
		.CreatePhysicsScene(false)
		.RequiresHitProxies(false) // Only Need hit proxies in an editor scene
		.CreateNavigation(false)
		.CreateAISystem(false)
		.ShouldSimulatePhysics(false)
		.SetTransactional(true)
		.SetDefaultGameMode(DefaultGameMode));

	WidgetWorld->InitializeActorsForPlay(FURL());

	Viewport = SNew(SWidgetViewport)
		.Mode(VieportRenderType)
		.WidgetWorld(WidgetWorld);

	if (bGenerateDefaultLight)
	{
		DirectionalLight = CastChecked<ADirectionalLight>(SpawnActor(ADirectionalLight::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector));
		DirectionalLight->GetLightComponent()->Intensity = PI;
		DirectionalLight->SetLightColor(FLinearColor::White);

		SkyLight = CastChecked<ASkyLight>(SpawnActor(ASkyLight::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector));
		USkyLightComponent* SkyComponent = SkyLight->GetLightComponent();
		SkyComponent->bLowerHemisphereIsBlack = false;
		SkyComponent->SourceType = ESkyLightSourceType::SLS_SpecifiedCubemap;
		SkyComponent->Intensity = 1.0f;
		SkyComponent->Mobility = EComponentMobility::Movable;

		if (CubeTexture)
		{
			SkyComponent->SetCubemap(CubeTexture);
		}

		USkyLightComponent::UpdateSkyCaptureContents(WidgetWorld);
		UReflectionCaptureComponent::UpdateReflectionCaptureContents(WidgetWorld);
	}

	SetBackgroundColor(BackgroundColor);
	SetOpacityForMaskMode(Opacity);


	if (bAutoSpawnActor)
	{
		SpawnWidgetHelperActor();
	}

	return Viewport.ToSharedRef();
}

AActor* UWidgetViewport::SpawnActor(TSubclassOf<AActor> Class, FVector Location /*= FVector(1.f, 1.f, 1.f)*/, FRotator Rotation /*= FRotator(1.f, 1.f, 1.f)*/, FVector Scale /*= FVector(1.f, 1.f, 1.f)*/)
{
	if (Viewport.IsValid())
	{

		FTransform Trans;
		Trans.SetLocation(Location);
		Trans.SetRotation(FQuat(Rotation));
		Trans.SetScale3D(Scale);
		return Viewport->SpawnActor(Class, Trans);
	}

	return nullptr;
}

AViewportWidgetHelper* UWidgetViewport::SpawnWidgetHelperActor(FVector Location /*= FVector(1.f, 1.f, 1.f)*/, FRotator Rotation /*= FRotator(1.f, 1.f, 1.f)*/, FVector Scale /*= FVector(1.f, 1.f, 1.f)*/)
{
	if (ViewportWidgetHelperClass)
	{
		ViewportWidgetHelper = Cast<AViewportWidgetHelper>(SpawnActor(ViewportWidgetHelperClass, Location, Rotation, Scale));
		SetCameraLocation(ViewportWidgetHelper->CameraComponent->GetComponentLocation());
		SetCameraRotation(ViewportWidgetHelper->CameraComponent->GetComponentRotation());
	}
	return ViewportWidgetHelper;
}

void UWidgetViewport::SetCameraLocation(FVector Location)
{
	if (Viewport.IsValid())
	{
		Viewport->SetLocation(Location);
	}
}

void UWidgetViewport::SetCameraRotation(FRotator Rotation)
{
	if (Viewport.IsValid())
	{
		Viewport->SetRotation(Rotation);
	}
}


void UWidgetViewport::SetFOV(float InFOV /*= 90*/)
{
	if (Viewport.IsValid())
	{
		Viewport->SetFOV(InFOV);
	}
}

float UWidgetViewport::GetFOV() const
{
	if (Viewport.IsValid())
	{
		Viewport->GetFOV();
	}
	return 0;
}

AStaticMeshActor* UWidgetViewport::AddStaticMesh(UStaticMesh* Mesh, FTransform Transform)
{
	if (Mesh && Viewport.IsValid())
	{
		return Viewport->AddStaticMesh(Mesh, Transform);
	}
	return nullptr;
}

ASkeletalMeshActor* UWidgetViewport::AddSkeletalMesh(USkeletalMesh* SkeletalMesh, FTransform Transform)
{
	if (SkeletalMesh && Viewport.IsValid())
	{
		return Viewport->AddSkeletalMesh(SkeletalMesh, Transform);
	}
	return nullptr;
}

void UWidgetViewport::GetAllActorsOfClass(TSubclassOf<AActor> Class, TArray<AActor*>& Result)
{
	if (!Viewport.IsValid()) return;

	Viewport->GetAllActorsOfClass(Class, Result);
}

void UWidgetViewport::SetBackgroundColor(FLinearColor Color)
{
	if (!Viewport.IsValid()) return;
	BackgroundColor = Color;
	Viewport->SetBackgroundColor(BackgroundColor);
}

ADirectionalLight* UWidgetViewport::GetDirectionalLight()
{
	return DirectionalLight;
}

ASkyLight* UWidgetViewport::GetSkyLight()
{
	return SkyLight;
}

void UWidgetViewport::SetOpacityForMaskMode(float InOpacity)
{
	if (Viewport.IsValid())
	{
		Opacity = InOpacity;
		Viewport->SetOpacityMaskMode(Opacity);
	}
}


void UWidgetViewport::SetNewObject(UObject* NewObj)
{
	if (ViewportWidgetHelper)
	{
		ViewportWidgetHelper->SetNewObject(NewObj);
		if (Viewport->GetViewportClient().IsValid()) 
		{			
			Viewport->GetViewportClient()->FocusViewportOnBox(ViewportWidgetHelper->GetComponentsBoundingBox());
		}
	}
	OnNewObject(NewObj);
}

#undef LOCTEXT_NAMESPACE

// Created by Bionic Ape. All rights reseved.


#include "Widgets/SWidgetViewport.h"
#include "Stats/Stats2.h"
#include "Brushes/SlateColorBrush.h"
#include "Rendering/DrawElements.h"
#include "Textures/SlateShaderResource.h"
#include "Slate/SlateTextures.h"
#include "RHIResources.h"
#include "Math/Vector2D.h"
#include "Modules/ModuleManager.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "RenderingThread.h"
#include "CanvasTypes.h"
#include "CanvasItem.h"
#include "RenderResource.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Templates/Casts.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EngineUtils.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Materials/Material.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Materials/MaterialInstanceDynamic.h"

SWidgetViewport::SWidgetViewport()
{
	MID = nullptr;
	bModeInitialized = false;
	Capture = nullptr;
	RenderTargetTexture = nullptr;
	ViewportSize = FIntPoint(0, 0);
	Material = nullptr;
	OpacityMask = 1.0f;
}

SWidgetViewport::~SWidgetViewport()
{
	
}

void SWidgetViewport::Construct(const FArguments& InArgs)
{
	ViewportMode = InArgs._Mode;
	
	SViewport::FArguments ParentArgs;
	SViewport::Construct(ParentArgs);

	ViewportClient = MakeShareable(new FWidgetViewportClient(InArgs._WidgetWorld));
	Viewport = MakeShareable(new FSceneViewport(ViewportClient.Get(), SharedThis(this)));

	// The viewport widget needs an interface so it knows what should render
	SetViewportInterface(Viewport.ToSharedRef());
// 
	if (ViewportMode == EViewportRenderType::BLEND_VIEWPORT)
	{
		SetBackgroundColor(FLinearColor(0, 0, 0, 0));
	}
}

void SWidgetViewport::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	Viewport->Invalidate();
	Viewport->Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	ViewportClient->Tick(InDeltaTime);

	if (ViewportMode == EViewportRenderType::MASKED_VIEWPORT && AllottedGeometry.GetLocalSize().X > 0 && !bModeInitialized)
	{
		ViewportSize = FIntPoint(AllottedGeometry.GetLocalSize().X, AllottedGeometry.GetLocalSize().Y);
		InitMaskMode();
	}

	if (Capture && bModeInitialized)
	{
		Capture->SetActorLocation(GetLocation());
		Capture->SetActorRotation(GetRotation());
		Capture->GetCaptureComponent2D()->FOVAngle = GetFOV();
	}
}

int32 SWidgetViewport::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (ViewportMode == EViewportRenderType::DEFAULT_VIEWPORT)
	{
		return SViewport::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}

	SCOPED_NAMED_EVENT(SViewport_OnPaint, FColor::Purple);

	ESlateDrawEffect DrawEffects = ESlateDrawEffect::None;

	DrawEffects |= ESlateDrawEffect::PreMultipliedAlpha;

	TSharedPtr<ISlateViewport> ViewportInterfacePin = ViewportInterface.Pin();

	// Tell the interface that we are drawing.
	if (ViewportInterfacePin.IsValid())
	{
		ViewportInterfacePin->OnDrawViewport(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}

	// Only draw a quad if not rendering directly to the back buffer
 	if (!ShouldRenderDirectly())
 	{
		if (ViewportInterfacePin.IsValid() && ViewportInterfacePin->GetViewportRenderTargetTexture() != nullptr)
		{
			if (ViewportMode == EViewportRenderType::BLEND_VIEWPORT || ViewportMode == EViewportRenderType::DEFAULT_VIEWPORT)
			{
				FSlateDrawElement::MakeViewport(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), ViewportInterfacePin, DrawEffects, FLinearColor::White);
			}
			
			//~ I will draw this on top because such is life
			if (ViewportMode == EViewportRenderType::MASKED_VIEWPORT && bModeInitialized && ViewportBrush.IsValid())
			{
				FLinearColor MaskColor = FLinearColor::White;
				MaskColor.A = OpacityMask;
				//Draw the mask;
				FSlateDrawElement::MakeBox(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(),
					ViewportBrush.Get(),
					ESlateDrawEffect::None,
					MaskColor
				);
			}

		}
	}
	
 	return LayerId;
}

void SWidgetViewport::InitMaskMode()
{
	if (ViewportMode != EViewportRenderType::MASKED_VIEWPORT) return;

	//~ Create Render Target;
	RenderTargetTexture = NewObject<UTextureRenderTarget2D>(GetTransientPackage(), NAME_None, RF_Transient);
	check(RenderTargetTexture);
	RenderTargetTexture->RenderTargetFormat = RTF_RGBA16f;
	RenderTargetTexture->ClearColor = FLinearColor::Black;
	RenderTargetTexture->bAutoGenerateMips = false;
	RenderTargetTexture->InitAutoFormat(ViewportSize.X * 1.5f, ViewportSize.Y * 1.5f);
	RenderTargetTexture->UpdateResourceImmediate(true);

	Material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), NULL, TEXT("/BionicApeCore/UI/Materials/M_MaskedUI")));
	check(Material);
	
	MID = UMaterialInstanceDynamic::Create(Material, nullptr);
	MID->AddToRoot();
	check(MID);
	MID->SetTextureParameterValue(FName("Texture"), RenderTargetTexture);

	
	ViewportBrush = MakeShareable(new FSlateBrush());
	ViewportBrush->SetResourceObject(MID);
	
	Capture = Cast<ASceneCapture2D>(SpawnActor(ASceneCapture2D::StaticClass(), FTransform()));
	Capture->GetCaptureComponent2D()->TextureTarget = RenderTargetTexture;

	bModeInitialized = true;
}

UWorld* SWidgetViewport::GetWorld() const
{
	if (ViewportClient.IsValid())
	{
		return ViewportClient->GetWorld();
	}
	return nullptr;
}

AActor* SWidgetViewport::SpawnActor(TSubclassOf<AActor> InClass, FTransform InTransform)
{
	return GetWorld()->SpawnActor<AActor>(InClass, InTransform);
}

AStaticMeshActor* SWidgetViewport::AddStaticMesh(UStaticMesh* InMesh, FTransform InTransform)
{
	if (InMesh)
	{
		AStaticMeshActor* Spawn = CastChecked<AStaticMeshActor>(SpawnActor(AStaticMeshActor::StaticClass(), InTransform));
		if (Spawn)
		{
			Spawn->GetStaticMeshComponent()->SetStaticMesh(InMesh);
			return Spawn;
		}
	}
	return nullptr;
}

ASkeletalMeshActor* SWidgetViewport::AddSkeletalMesh(USkeletalMesh* InSkeletalMesh, FTransform InTransform)
{
	if (InSkeletalMesh)
	{
		ASkeletalMeshActor* Spawn = CastChecked<ASkeletalMeshActor>(SpawnActor(ASkeletalMeshActor::StaticClass(), InTransform));
		if (Spawn)
		{
			Spawn->GetSkeletalMeshComponent()->SetSkeletalMesh(InSkeletalMesh);
			return Spawn;
		}
	}
	return nullptr;
}

void SWidgetViewport::GetAllActorsOfClass(TSubclassOf<AActor> Class, TArray<AActor*>& Result)
{
	Result.Empty();
	for (TActorIterator<AActor> It(GetWorld(), Class); It; ++It)
	{
		AActor* Actor = *It;
		Result.Add(Actor);
	}
}

void SWidgetViewport::SetLocation(const FVector& InLocation)
{
	ViewportClient->SetLocation(InLocation);
}

void SWidgetViewport::SetRotation(const FRotator& InRotation)
{
	ViewportClient->SetRotation(InRotation);
}

void SWidgetViewport::SetFOV(const float& InFOV)
{
	ViewportClient->SetFOV(InFOV);
}

float SWidgetViewport::GetFOV() const
{
	return ViewportClient->GetFOV();
}

FVector SWidgetViewport::GetLocation() const
{
	return ViewportClient->GetLocation();
}

FRotator SWidgetViewport::GetRotation() const
{
	return ViewportClient->GetRotation();
}

void SWidgetViewport::SetBackgroundColor(const FLinearColor& InColor)
{
	ViewportClient->SetBackgroundColor(InColor);
}

void SWidgetViewport::SetOpacityMaskMode(float InOpacity)
{
	OpacityMask = InOpacity;
}
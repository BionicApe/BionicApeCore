// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"


#include "Slate/SceneViewport.h"

#include "Styling/SlateBrush.h"

#include "BionicApeUITypes.h"
#include "Widgets/SViewport.h"
#include "WidgetViewportClient.h"

#include "Rendering/RenderingCommon.h"

#include "UObject/GCObject.h"


class AStaticMeshActor;
class ASkeletalMeshActor;
class UStaticMesh;
class USkeletalMesh;
class UMaterial;
class UMaterialExpressionTextureSample;
class UTextureRenderTarget2D;
class ASceneCapture2D;
class UMaterialExpressionOneMinus;
class UMaterialInstanceDynamic;
class UMaterialInterface;


/**
 *
 */
class BIONICAPEUI_API SWidgetViewport : public SViewport
{
	SLATE_BEGIN_ARGS(SWidgetViewport)
		: _Mode(EViewportRenderType::DEFAULT_VIEWPORT)
	{
	}
	SLATE_ARGUMENT(EViewportRenderType, Mode)
		SLATE_ARGUMENT(UWorld*, WidgetWorld)
		SLATE_END_ARGS()

		SWidgetViewport();
	~SWidgetViewport();

	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;


private:

	class FInternalGC : public FGCObject
	{
	public:
		FInternalGC(SWidgetViewport* InWidgetViewport)
			: Object(InWidgetViewport)
		{

		}

		//~ FGCObject interface
		virtual void AddReferencedObjects(FReferenceCollector& InCollector) override
		{
			InCollector.AddReferencedObject(Object->MID);
			InCollector.AddReferencedObject(Object->RenderTargetTexture);
			InCollector.AddReferencedObject(Object->Capture);
			InCollector.AddReferencedObject(Object->Material);
		}

	private:
		SWidgetViewport* Object;
	};


protected:
	TSharedPtr<FWidgetViewportClient> ViewportClient;

	TSharedPtr<FSceneViewport> Viewport;

	EViewportRenderType ViewportMode;

	UMaterialInterface* Material;
	UMaterialInstanceDynamic* MID;
	UTextureRenderTarget2D* RenderTargetTexture;
	float OpacityMask;
	ASceneCapture2D* Capture;

	FIntPoint ViewportSize;
	bool bModeInitialized;

	/** The Slate brush that renders the material. */
	TSharedPtr<FSlateBrush> ViewportBrush;

private:
	void InitMaskMode();

public:

	UWorld* GetWorld() const;
	AActor* SpawnActor(TSubclassOf<AActor> InClass, FTransform InTransform);
	AStaticMeshActor* AddStaticMesh(UStaticMesh* InMesh, FTransform InTransform);
	ASkeletalMeshActor* AddSkeletalMesh(USkeletalMesh* InSkeletalMesh, FTransform InTransform);
	void GetAllActorsOfClass(TSubclassOf<AActor> Class, TArray<AActor*>& Result);
	void SetLocation(const FVector& InLocation);
	void SetRotation(const FRotator& InRotation);
	void SetFOV(const float& InFOV);
	float GetFOV() const;
	FVector GetLocation() const;
	FRotator GetRotation() const;

	TSharedPtr<FWidgetViewportClient> GetViewportClient() {return ViewportClient;};

	void SetBackgroundColor(const FLinearColor& InColor);
	void SetOpacityMaskMode(float InOpacity);
};

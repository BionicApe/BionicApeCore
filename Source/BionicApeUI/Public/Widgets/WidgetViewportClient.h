// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "SceneManagement.h"
#include "Camera/CameraTypes.h"
#include "PreviewScene.h"
#include "UnrealClient.h"


/**
 * 
 */
class BIONICAPEUI_API FWidgetViewportClient : public FCommonViewportClient, public FViewElementDrawer
{
protected:

	FVector Location;
	FRotator Rotation;
	float FOV;

	TWeakObjectPtr<UWorld> WidgetWorld;

	FMinimalViewInfo ViewInfo;

	FLinearColor BackgroundColor;

	FViewport* Viewport;

	FSceneViewStateReference ViewStateReference;

	FEngineShowFlags EngineShowFlags;


public:

	FWidgetViewportClient(UWorld* CustomWorld);

	virtual ~FWidgetViewportClient();

	//~ FViewportClient
	virtual UWorld* GetWorld() const override;
	virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;

	//~ FViewElementDrawer
	virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;

	virtual void Tick(float Delta);

	virtual FSceneView* CalcSceneView(FSceneViewFamily* ViewFamility);


	void SetBackgroundColor(FLinearColor InColor);
	FLinearColor GetBackgroundColor() const;

	void SetLocation(const FVector& InLocation);
	void SetRotation(const FRotator& InRotation);
	void SetFOV(const float& InFOV);
	float GetFOV() const;

	const FVector& GetLocation() const;
	const FRotator& GetRotation() const;

	void SetEngineShowFlags(FEngineShowFlags InEngineShowFlags);

	/**
	 * Focuses the viewport to the center of the bounding box ensuring that the entire box is in view
	 *
	 * @param BoundingBox			The box to focus
	 * @param bUpdateLinkedOrthoViewports	Whether or not to updated linked viewports when this viewport changes
	 * @param bInstant			Whether or not to focus the viewport instantly or over time
	 */
	void FocusViewportOnBox(const FBox& BoundingBox, bool bInstant = false);

};
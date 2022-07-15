// Copyright 2020 Jorge CR. All Rights Reserved.


#include "Widgets/WidgetViewportClient.h"
#include "EngineUtils.h"
#include "LegacyScreenPercentageDriver.h"
#include "EngineModule.h"
#include "Engine/World.h"
#include "Components/LineBatchComponent.h"
#include "Engine/LocalPlayer.h"

FWidgetViewportClient::FWidgetViewportClient(UWorld* CustomWorld)
	: Viewport(nullptr)
	, EngineShowFlags(ESFIM_Game)
{
	WidgetWorld = CustomWorld;
	FSceneInterface* Scene = GetWorld()->Scene;
	ViewStateReference.Allocate(Scene ? Scene->GetFeatureLevel() : GMaxRHIFeatureLevel);
	BackgroundColor = FLinearColor::Transparent;
	FOV = 90;
	Location = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;
}

FWidgetViewportClient::~FWidgetViewportClient()
{

}

UWorld* FWidgetViewportClient::GetWorld() const
{
	return (WidgetWorld.IsValid()) ? WidgetWorld.Get() : GWorld;
}

void FWidgetViewportClient::Draw(FViewport* InViewport, FCanvas* Canvas)
{
	FViewport* ViewportBackup = Viewport;
	Viewport = InViewport ? InViewport : Viewport;

	// Determine whether we should use world time or real time based on the scene.
	float TimeSeconds;
	float RealTimeSeconds;
	float DeltaTimeSeconds;

	UWorld* World = GetWorld();
	TimeSeconds = FApp::GetCurrentTime() - GStartTime;
	RealTimeSeconds = FApp::GetCurrentTime() - GStartTime;
	DeltaTimeSeconds = FApp::GetDeltaTime();

	//EngineShowFlags.SetWireframe(true);

	// Setup a FSceneViewFamily/FSceneView for the viewport.
	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
		Canvas->GetRenderTarget(),
		WidgetWorld->Scene,
		EngineShowFlags)
		.SetWorldTimes(TimeSeconds, DeltaTimeSeconds, RealTimeSeconds)
		.SetRealtimeUpdate(true));

	// Get DPI derived view fraction.
	float GlobalResolutionFraction = GetDPIDerivedResolutionFraction();

	// Force screen percentage show flag for High DPI.
	ViewFamily.EngineShowFlags.ScreenPercentage = false;

	FSceneView* View = CalcSceneView(&ViewFamily);

	ViewFamily.SetScreenPercentageInterface(new FLegacyScreenPercentageDriver(
		ViewFamily, GlobalResolutionFraction, /* AllowPostProcessSettingsScreenPercentage = */ false));

	FSlateRect SafeFrame;
	View->CameraConstrainedViewRect = View->UnscaledViewRect;

	Canvas->Clear(BackgroundColor);

	// workaround for hacky renderer code that uses GFrameNumber to decide whether to resize render targets
	--GFrameNumber;
	GetRendererModule().BeginRenderingViewFamily(Canvas, &ViewFamily);

	// Remove temporary debug lines.
	// Possibly a hack. Lines may get added without the scene being rendered etc.
	if (World->LineBatcher != NULL && (World->LineBatcher->BatchedLines.Num() || World->LineBatcher->BatchedPoints.Num()))
	{
		World->LineBatcher->Flush();
	}

	if (World->ForegroundLineBatcher != NULL && (World->ForegroundLineBatcher->BatchedLines.Num() || World->ForegroundLineBatcher->BatchedPoints.Num()))
	{
		World->ForegroundLineBatcher->Flush();
	}

	Viewport = ViewportBackup;
}

void FWidgetViewportClient::Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	FViewElementDrawer::Draw(View, PDI);
}

void FWidgetViewportClient::Tick(float Delta)
{
	if (GIntraFrameDebuggingGameThread) return;

	if (!WidgetWorld->bBegunPlay)
	{
		for (FActorIterator It(WidgetWorld.Get()); It; ++It)
		{
			It->DispatchBeginPlay();
		}
		WidgetWorld->bBegunPlay = true;
	}

	// Tick
	WidgetWorld->Tick(LEVELTICK_All, Delta);
}

FSceneView* FWidgetViewportClient::CalcSceneView(FSceneViewFamily* ViewFamily)
{
	FSceneViewInitOptions ViewInitOptions;

	const FVector& ViewLocation = GetLocation();
	const FRotator& ViewRotation = GetRotation();

	const FIntPoint ViewportSizeXY = Viewport->GetSizeXY();

	FIntRect ViewRect = FIntRect(0, 0, ViewportSizeXY.X, ViewportSizeXY.Y);
	ViewInitOptions.SetViewRectangle(ViewRect);

	ViewInitOptions.ViewOrigin = ViewLocation;

	ViewInitOptions.ViewRotationMatrix = FInverseRotationMatrix(ViewRotation);
	ViewInitOptions.ViewRotationMatrix = ViewInitOptions.ViewRotationMatrix * FMatrix(
		FPlane(0, 0, 1, 0),
		FPlane(1, 0, 0, 0),
		FPlane(0, 1, 0, 0),
		FPlane(0, 0, 0, 1));

	check(FVector::Distance(ViewInitOptions.ViewRotationMatrix.GetScaleVector(), FVector::OneVector) < KINDA_SMALL_NUMBER);

	//@TODO: Should probably be locally configurable (or just made into a FMinimalViewInfo property)
	const EAspectRatioAxisConstraint AspectRatioAxisConstraint = GetDefault<ULocalPlayer>()->AspectRatioAxisConstraint;

	ViewInitOptions.ViewFamily = ViewFamily;
	ViewInitOptions.SceneViewStateInterface = ViewStateReference.GetReference();
	ViewInitOptions.ViewElementDrawer = this;

	ViewInitOptions.BackgroundColor = GetBackgroundColor();
	ViewInitOptions.FOV = FOV;
	ViewInitOptions.DesiredFOV = FOV;
	ViewInfo.FOV = FOV;

	FMinimalViewInfo::CalculateProjectionMatrixGivenView(ViewInfo, AspectRatioAxisConstraint, Viewport, /*inout*/ ViewInitOptions);

	FSceneView* View = new FSceneView(ViewInitOptions);
	View->FOV = FOV;

	ViewFamily->Views.Add(View);

	View->StartFinalPostprocessSettings(ViewLocation);
	View->EndFinalPostprocessSettings(ViewInitOptions);
	return View;
}

void FWidgetViewportClient::SetBackgroundColor(FLinearColor InColor)
{
	BackgroundColor = InColor;
}

FLinearColor FWidgetViewportClient::GetBackgroundColor() const
{
	return BackgroundColor;
}

void FWidgetViewportClient::SetViewport(FViewport* InViewport)
{
	Viewport = InViewport;
}

void FWidgetViewportClient::SetLocation(const FVector& InLocation)
{
	Location = InLocation;
}

void FWidgetViewportClient::SetRotation(const FRotator& InRotation)
{
	Rotation = InRotation;
}

void FWidgetViewportClient::SetFOV(const float& InFOV)
{
	FOV = InFOV;
}

float FWidgetViewportClient::GetFOV() const
{
	return FOV;
}

const FVector& FWidgetViewportClient::GetLocation() const
{
	return Location;
}

const FRotator& FWidgetViewportClient::GetRotation() const
{
	return Rotation;
}

void FWidgetViewportClient::SetEngineShowFlags(FEngineShowFlags InEngineShowFlags)
{
	EngineShowFlags = InEngineShowFlags;
}

void FWidgetViewportClient::FocusViewportOnBox(const FBox& BoundingBox, bool bInstant /*= false*/)
{
	if (Viewport)
	{

		const FVector Position = BoundingBox.GetCenter();
		float Radius = FMath::Max(BoundingBox.GetExtent().Size(), 10.f);


		//Some items overlap wit the camera's near plane so we need some offset
		float RadiusAdditionalOffset = 5.0f;
		Radius += RadiusAdditionalOffset;

		float const AspectToUse = Viewport->GetDesiredAspectRatio();
		FIntPoint const ViewportSize = Viewport->GetSizeXY();

		/**
		 * We need to make sure we are fitting the sphere into the viewport completely, so if the height of the viewport is less
		 * than the width of the viewport, we scale the radius by the aspect ratio in order to compensate for the fact that we have
		 * less visible vertically than horizontally.
		 */
		if (AspectToUse > 1.0f)
		{
			Radius *= AspectToUse;
		}

		/**
		 * Now that we have a adjusted radius, we are taking half of the viewport's FOV,
		 * converting it to radians, and then figuring out the camera's distance from the center
		 * of the bounding sphere using some simple trig.  Once we have the distance, we back up
		 * along the camera's forward vector from the center of the sphere, and set our new view location.
		 */

		const float HalfFOVRadians = FMath::DegreesToRadians(GetFOV() / 2.0f);
		const float DistanceFromSphere = Radius / FMath::Tan(HalfFOVRadians);
		FVector CameraOffsetVector = GetRotation().Vector() * -DistanceFromSphere;

		//ViewTransform.SetLookAt(Position);
		SetLocation(Position + CameraOffsetVector);
	}
}

// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "Components/Widget.h"

#include "Widgets/SWidgetViewport.h"
#include "BionicApeUITypes.h"

#include "WidgetViewport.generated.h"

class ASkeletalMeshActor;
class USkeletalMesh;
class AStaticMeshActor;
class UStaticMesh;
class ADirectionalLight;
class ASkyLight;
class AViewportWidgetHelper;
class UObject;


/**
 * 
 */
UCLASS()
class BIONICAPEUI_API UWidgetViewport : public UWidget
{
	GENERATED_UCLASS_BODY()

public:

#if WITH_EDITOR
	// UWidget interface
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

private:
	UPROPERTY(Transient)
	UWorld* WidgetWorld;

	UPROPERTY(Transient)
	ADirectionalLight* DirectionalLight;

	UPROPERTY(Transient)
	ASkyLight* SkyLight;

public:
	
	UPROPERTY(EditAnywhere, Category = Appearance)
	FLinearColor BackgroundColor;

	UPROPERTY(EditAnywhere, Category = Appearance)
	EViewportRenderType VieportRenderType;

	UPROPERTY(EditAnywhere, Category = Appearance)
	bool bGenerateDefaultLight;

	UPROPERTY(EditAnywhere, Category = Appearance)
	bool bAutoSpawnActor = true;

	UPROPERTY(EditAnywhere, Category = Appearance)
	TSubclassOf<AViewportWidgetHelper> ViewportWidgetHelperClass;

	UPROPERTY(VisibleAnywhere, Category = Appearance)
	AViewportWidgetHelper* ViewportWidgetHelper;
	
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (editcondition = "bGenerateDefaultLight"))
	class UTextureCube* CubeTexture;

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (editcondition = "VieportRenderType == EViewportRenderType::MASKED_VIEWPORT"))
	float Opacity;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Viewport", meta = (DeterminesOutputType = "Class"))
	AActor* SpawnActor(TSubclassOf<AActor> Class, FVector Location = FVector(1.f, 1.f, 1.f), FRotator Rotation = FRotator(1.f, 1.f, 1.f), FVector Scale = FVector(1.f, 1.f, 1.f));

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	AViewportWidgetHelper* SpawnWidgetHelperActor(FVector Location = FVector(1.f, 1.f, 1.f), FRotator Rotation = FRotator(1.f, 1.f, 1.f), FVector Scale = FVector(1.f, 1.f, 1.f));

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	void SetCameraLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	void SetCameraRotation(FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	void SetFOV(float InFOV = 90);

	UFUNCTION(BlueprintPure, Category = "Viewport")
	float GetFOV() const;

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	AStaticMeshActor* AddStaticMesh(UStaticMesh* Mesh, FTransform Transform);

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	ASkeletalMeshActor* AddSkeletalMesh(USkeletalMesh* SkeletalMesh, FTransform Transform);

	UFUNCTION(BlueprintCallable, Category = "Viewport", meta = (DeterminesOutputType = "Class", DynamicOutputParam = "OutActors"))
	void GetAllActorsOfClass(TSubclassOf<AActor> Class, TArray<AActor*>& Result);

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	void SetBackgroundColor(FLinearColor Color);

	UFUNCTION(BlueprintPure, Category = "Viewport")
	ADirectionalLight* GetDirectionalLight();

	UFUNCTION(BlueprintPure, Category = "Viewport")
	ASkyLight* GetSkyLight();

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	void SetOpacityForMaskMode(float InOpacity);

	UFUNCTION(BlueprintImplementableEvent, Category = "Viewport")
	void OnNewObject(UObject* NewObj);

	virtual void SetNewObject(UObject* NewObj);

protected:
	
	TSharedPtr<SWidgetViewport> Viewport;		
};

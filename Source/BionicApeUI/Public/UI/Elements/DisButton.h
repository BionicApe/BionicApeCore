// Move 36 Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "DisButton.generated.h"

/**
 * This class is compatible with Styles when a Gamepad is used. (default UButton only works with mouse/touch)
 */
UCLASS(BlueprintType, Blueprintable)
class BIONICAPEUI_API UDisButton : public UButton
{
	GENERATED_BODY()

	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnRebuildWidget"))
	void OnRebuildWidget();
};

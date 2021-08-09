// Move 36 Studio

#pragma once

#include "UObject/Interface.h"
#include "BionicApeHUDInterface.generated.h"

/**
*
*/
UINTERFACE(Blueprintable)
class BIONICAPEUI_API UBionicApeHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class IBionicApeHUDInterface
{
	GENERATED_BODY()

public:

	virtual void ShowAlert(bool bIsSuccessful, const FString& AlertMessage) = 0;
};
// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWindow.h"


class SMeshFromBlueprint : public SWindow
{
public:

	FExtractOptions ExtractOptions;

public:

	void Construct(const FArguments& InArgs);
};
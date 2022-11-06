// Created by Bionic Ape. All Rights Reserved.

#include "TypeActions/[Factory]TypeActions.h"
#include "[PathTo[Factory]Class]/[Factory].h"

#define LOCTEXT_NAMESPACE "[Factory]_TypeActions"

F[Factory]TypeActions::F[Factory]TypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText F[Factory]TypeActions::GetName() const
{
	return LOCTEXT("F[Factory]TypeActionsName", "[Factory]");
}

FColor F[Factory]TypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* F[Factory]TypeActions::GetSupportedClass() const
{
	return U[Factory]::StaticClass();
}

uint32 F[Factory]TypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE
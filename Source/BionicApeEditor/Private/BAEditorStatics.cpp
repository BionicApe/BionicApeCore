// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "BAEditorStatics.h"
#include "Editor/EditorEngine.h"
#include "Engine.h"

UWorld* UBAEditorStatics::GetEditorMainWorld()
{
	return GEditor->GetEditorWorldContext().World();
}

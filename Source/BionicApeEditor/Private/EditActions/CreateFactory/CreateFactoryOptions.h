// Created by Bionic Ape. All Rights Reserved.

#pragma once

UENUM()
enum class EFactoryType : uint8
{
	Simple = 0,
	Advanced,
	// ...
	Count
};
ENUM_RANGE_BY_COUNT(EFactoryType, EFactoryType::Count)

struct FCreateFactoryOptions
{
	FString ModuleName;
	EFactoryType FactoryType;
	FString FactoryName;
	FString TargetPath;
	bool bReplaceFileIfExists;
};
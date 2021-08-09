// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

//
//USTRUCT(BlueprintType)
//struct FBAColorPalette
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Color1;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum01;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum02;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum03;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum04;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum05;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum06;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum07;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum08;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum09;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum10;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum11;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum12;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum13;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum14;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum15;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum16;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum17;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum18;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum19;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum20;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor GeneralExpectrum21;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Light1;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Light2;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Light3;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Light4;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Light5;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Light6;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Light7;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Medium1;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Medium2;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Medium3;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Medium4;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Medium5;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Medium6;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Medium7;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Dark1;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Dark2;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Dark3;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Dark4;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Dark5;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Dark6;
//
//	UPROPERTY(Category = "FocusInteractions", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//	FLinearColor Dark7;
//
//
//	FBAColorPalette()
//	{
//	}
//};
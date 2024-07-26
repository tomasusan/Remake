// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API UFileBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static bool SaveTextArray(FString Directory, FString FileName, const TArray<FString>& TextArray, bool Overwrite);
	static bool LoadTextArray(FString Directory, FString FileName, TArray<FString>& Result);
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "FileBlueprintFunctionLibrary.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

bool UFileBlueprintFunctionLibrary::SaveTextArray(FString Directory, FString FileName, const TArray<FString>& TextArray, const bool Overwrite)
{
	Directory+="//";
	Directory+=FileName;

	if(!Overwrite)
	{
		if(FPlatformFileManager::Get().GetPlatformFile().FileExists(*Directory))
		{
			return false;
		}
	}

	return FFileHelper::SaveStringArrayToFile(TextArray, *Directory);
}

bool UFileBlueprintFunctionLibrary::LoadTextArray(FString Directory, FString FileName, TArray<FString>& Result)
{
	Directory+="//";
	Directory+=FileName;

	return FFileHelper::LoadFileToStringArray(Result, *Directory);
	
}

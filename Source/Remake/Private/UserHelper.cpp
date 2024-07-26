// Fill out your copyright notice in the Description page of Project Settings.


#include "UserHelper.h"
#include "FileBlueprintFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(UserHelperLog, All, All);

UserHelper::UserHelper()
{
}

void UserHelper::GetUserInfo(FString Username, FString Psw)
{
	this->CurrentUsername = Username;
	this->CurrentPsw = Psw;
}

bool UserHelper::IsValid(int32& Score)
{
	const FString Directory =  "E://UEPJ//Saved//Game//Saved";
	FString FileName = "general.data";

	UE_LOG(UserHelperLog, Warning, TEXT("Current Username:%s"),*CurrentUsername);
	UE_LOG(UserHelperLog, Warning, TEXT("Current Psw:%s"),*CurrentPsw);

	TArray<FString> Result;
	
	UFileBlueprintFunctionLibrary::LoadTextArray(Directory, FileName, Result);

	int32 Num = FCString::Atoi(*Result[0]);

	UE_LOG(UserHelperLog, Warning, TEXT("current file: %d"), Num);

	for(int i=0;i<Num;i++)
	{
		FileName="Saved";
		FileName+=FString::FromInt(i+1);
		FileName+=".data";

		UE_LOG(UserHelperLog, Warning, TEXT("Current File:%s"),*FileName);

		UFileBlueprintFunctionLibrary::LoadTextArray(Directory, FileName, Result);

		if(Result[0]==CurrentUsername)
		{
			UE_LOG(UserHelperLog, Warning, TEXT("Find Account"));
			if(Result[1].Equals(CurrentPsw))
			{
				UE_LOG(UserHelperLog, Warning, TEXT("Psw Match!"));
				Score = FCString::Atoi(*Result[2]);
				return true;
			}
			else
			{
				UE_LOG(UserHelperLog, Warning, TEXT("Psw Dismatch!"));
			}
		}
		else
		{
			UE_LOG(UserHelperLog, Warning, TEXT("No Account Found!"));
		}
	}

	
	
	return false;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
using namespace std;

/**
 * 
 */
class REMAKE_API UserHelper
{
private:
	FString CurrentUsername;
	FString CurrentPsw;
public: 
	UserHelper();

	void GetUserInfo(FString Username, FString Psw);
	bool IsValid(int32& Score);
};

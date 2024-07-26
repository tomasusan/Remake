// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UserHelper;

/**
 * 
 */
UCLASS()
class REMAKE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UserHelper* Helper;

public:
	UFUNCTION(BlueprintCallable)
	void WidgetInit();
	
	UFUNCTION(BlueprintCallable)
	void LoadInfo(const FString& Username, const FString& Psw);

	UFUNCTION(BlueprintCallable)
	bool IsInfoValid(int32& Score);
};

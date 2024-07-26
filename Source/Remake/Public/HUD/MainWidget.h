// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RemakeCoreTypes.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UTime* Time;

public:
	UFUNCTION(BlueprintCallable)
	void InitTime(int32 m, int32 s, int32 ms);

	UFUNCTION(BlueprintCallable)
	UTime* GetWidgetTime() { return Time; }
};

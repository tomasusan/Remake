// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RemakeCoreTypes.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowHint();

	UFUNCTION(BlueprintImplementableEvent)
	void HideHint();

	UFUNCTION(BlueprintCallable)
	FBasicInteractableItemInfo GetDetectedItemInfo();
};

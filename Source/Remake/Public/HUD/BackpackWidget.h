// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RemakeCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "BackpackWidget.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API UBackpackWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateItems(TArray<FPickItemData>& Items);
};

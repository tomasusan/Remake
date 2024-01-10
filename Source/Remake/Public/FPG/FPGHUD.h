// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPGHUD.generated.h"

class UMainUserWidget;
/**
 * 
 */
UCLASS()
class REMAKE_API AFPGHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Widget")
	TSubclassOf<UMainUserWidget> MainUserWidgetClass;

private:
	UPROPERTY()
	UMainUserWidget* MainUserWidget;
	
};

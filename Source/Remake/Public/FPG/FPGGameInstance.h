// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API UFPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetCurrentHUD(AHUD* HUD) { CurrentHUD = HUD; }
	AHUD* GetCurrentHUD() const { return CurrentHUD; }

private:
	UPROPERTY()
	AHUD* CurrentHUD = nullptr;
};

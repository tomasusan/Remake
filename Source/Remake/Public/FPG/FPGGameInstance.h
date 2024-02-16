// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseShop.h"
#include "FPGGameInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class REMAKE_API UFPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetCurrentHUD(AHUD* HUD) { CurrentHUD = HUD; }
	AHUD* GetCurrentHUD() const { return CurrentHUD; }
	UFUNCTION(BlueprintCallable)
	ABaseShop* GetCurrentActiveShop() const { return CurrentActiveShop; }
	UFUNCTION(BlueprintCallable)
	void SetCurrentActiveShop(ABaseShop* Shop) { CurrentActiveShop = Shop; }

private:
	UPROPERTY()
	AHUD* CurrentHUD = nullptr;

	UPROPERTY()
	ABaseShop* CurrentActiveShop = nullptr;
};

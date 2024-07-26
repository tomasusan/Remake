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

	UFUNCTION(BlueprintCallable)
	void GetUserInfo(FString& GetUsername, int32& GetScore) const
	{
		GetUsername = this->Username;
		GetScore = this->Score;
	}

	UFUNCTION(BlueprintCallable)
	void SetUserInfo(const FString& SetUsername, const int32& SetScore)
	{
		this->Username = SetUsername;
		this->Score = SetScore;
	}

	UFUNCTION(BlueprintCallable)
	void AddScore(){CurrentScore+=1;}

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentScore()const {return CurrentScore;}

private:
	UPROPERTY()
	AHUD* CurrentHUD = nullptr;

	UPROPERTY()
	ABaseShop* CurrentActiveShop = nullptr;

	UPROPERTY()
	FString Username="NULL";

	UPROPERTY()
	int32 Score=-1;

	UPROPERTY()
	int32 CurrentScore=0;
};

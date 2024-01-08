// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RemakeCoreTypes.h"
#include "ShopComponent.generated.h"


class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMAKE_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShopComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default")
	TArray<FShopItemData> ShopItems;
	
private:
	TArray<FShopItemData> CurrentItems;
	void InitShop();
	void Sell(const int32 Index);

	UPROPERTY()
	ABaseCharacter* OwningCharacter;
	
};

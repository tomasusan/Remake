// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RemakeCoreTypes.h"
#include "ShopComponent.generated.h"


class ABaseShop;
class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMAKE_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShopComponent();

	UFUNCTION(BlueprintCallable)
	void GetItems(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo);

	UFUNCTION(BlueprintCallable)
	void GetItemByType(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo, EItemType Type);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DefaultInfo")
	TMap<FName, int32> InitItemMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DefaultInfo")
	UDataTable* BasicItemInfoTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DefaultInfo")
	UDataTable* ShopItemInfoTable;
	
private:
	
	TArray<FShopItemData> ShopItems;
	void InitShop();
	void Sell(const int32 Index);

	UPROPERTY()
	ABaseShop* OwningCharacter;
	
};

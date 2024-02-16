// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RemakeCoreTypes.h"
#include "MainUserWidget.generated.h"

class UBackpackCell;
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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenShopWidget();

	UFUNCTION(BlueprintCallable)
	FBasicInteractableItemInfo GetDetectedItemInfo();

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UBackpackCell> GetBackpackCellClass() const {return BackpackCellClass;}

	UFUNCTION(BlueprintCallable)
	void GetCurrentItems(TArray<FBasicInteractableItemInfo>& Items);

	UFUNCTION(BlueprintCallable)
	void GetItemsByType(TArray<FBasicInteractableItemInfo>& Items,const EItemType Type);

	UFUNCTION(BlueprintCallable)
	void GetShopItems(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo);

	UFUNCTION(BlueprintCallable)
	void GetShopItemsByType(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo,const EItemType Type);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateHintInfo();

	UFUNCTION(BlueprintCallable)
	void AddFavourite(FShopItemData NewFavourite);

	UFUNCTION(BlueprintCallable)
	void GetFavourite(TArray<FShopItemData>& Favourites);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Backpack")
	TSubclassOf<UBackpackCell> BackpackCellClass;
};

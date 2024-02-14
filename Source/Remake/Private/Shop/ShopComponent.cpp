// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/ShopComponent.h"
#include "BaseCharacter.h"
#include "BaseShop.h"

DEFINE_LOG_CATEGORY_STATIC(ShopComponentLog, All, All);

// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningCharacter = Cast<ABaseShop>(GetOwner());
	checkf(OwningCharacter, TEXT("Owning Character Cast Fail"));
	InitShop();
}

void UShopComponent::GetItems(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo)
{
	TArray<FBasicInteractableItemInfo> RetItems;
	for(auto Item:ShopItems)
	{
		//UE_LOG(ShopComponentLog, Warning, TEXT("%s: %d"), *Item.)
		auto NewItem = BasicItemInfoTable->FindRow<FBasicInteractableItemInfo>(Item.ItemName, TEXT("Casting Shop Item to Base Interactable Item"), false);
		checkf(NewItem, TEXT("No Item Found: %s"), *Item.ItemName.ToString());
		NewItem->CurrentAmount = Item.InitAmount;
		RetItems.Add(*NewItem);
	}
	Items = RetItems;
	ShopItemInfo = ShopItems;
}

void UShopComponent::GetItemByType(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo, EItemType Type)
{
	TArray<FBasicInteractableItemInfo> RetItems;
	TArray<FShopItemData> RetItemShopInfo;
	for(auto Item:ShopItems)
	{
		auto NewItem = BasicItemInfoTable->FindRow<FBasicInteractableItemInfo>(Item.ItemName, TEXT("Casting Shop Item to Base Interactable Item"), false);
		checkf(NewItem, TEXT("No Item Found"));
		NewItem->CurrentAmount = Item.InitAmount;
		if(NewItem->Type == Type)
		{
			RetItems.Add(*NewItem);
			RetItemShopInfo.Add(Item);
		}
	}
	Items = RetItems;
	ShopItemInfo = RetItemShopInfo;
}


void UShopComponent::InitShop()
{
	for (auto InitItem : InitItemMap)
	{
		UE_LOG(ShopComponentLog, Warning, TEXT("%s loading %s: %d"), *GetName(), *InitItem.Key.ToString(), InitItem.Value);
		auto NewShopItem = ShopItemInfoTable->FindRow<FShopItemData>(
			InitItem.Key,
			TEXT("Get Shop Item From Shop Table"),
			true);
		checkf(NewShopItem, TEXT("No Shop Table Row Found: %s"), *InitItem.Key.ToString());
		NewShopItem->InitAmount = InitItem.Value;
		ShopItems.Add(*NewShopItem);
	}
}

void UShopComponent::Sell(const int32 Index)
{
}

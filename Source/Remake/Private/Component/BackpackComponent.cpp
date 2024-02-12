#include "Component/BackpackComponent.h"

UBackpackComponent::UBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();
	//BackpackWidget->Call();
}

void UBackpackComponent::PickItem(FBasicInteractableItemInfo ItemData)
{
	if (!ItemData.bCanOverlay)
	{
		ItemData.CurrentAmount = 1;
		Items.Add(ItemData);
		return;
	}
	for (auto& Item : Items)
	{
		if (Item.ItemName == ItemData.ItemName)
		{
			if (Item.CurrentAmount == Item.MaxAmount)
			{
				continue;
			}
			Item.CurrentAmount++;
			return;
		}
	}
	ItemData.CurrentAmount = 1;
	Items.Add(ItemData);
}

void UBackpackComponent::ReceiveShopItem(const FShopItemData& ShopItemData)
{
}

void UBackpackComponent::UseItem(const int32 Index)
{
}

void UBackpackComponent::ThrowItem(const int32 Index)
{
}

void UBackpackComponent::SwitchBackpackOpen()
{
}

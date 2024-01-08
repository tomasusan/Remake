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

void UBackpackComponent::PickItem(const FPickItemData& ItemData)
{
	for(auto& Item:Items)
	{
		if(Item.ItemName==ItemData.ItemName)
		{
			if(Item.CurrentAmount<Item.MaxAmount)
			{
				Item.CurrentAmount++;
				return;
			}
			else
			{
				goto Add;
			}
		}
	}
	Add:
		auto NewItem = ItemData;
		NewItem.CurrentAmount = 1;
		Items.Add(NewItem);
}

void UBackpackComponent::ReceiveShopItem(const FShopItemData& ShopItemData)
{
	const auto NewItem = *ItemDataTable->FindRow<FPickItemData>(ShopItemData.ItemName, FString("Convert From Shop Item to PickItem"));
	PickItem(NewItem);
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


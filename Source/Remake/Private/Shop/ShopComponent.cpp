// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/ShopComponent.h"
#include "BaseCharacter.h"

// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningCharacter = Cast<ABaseCharacter>(GetOwner());
	checkf(OwningCharacter, TEXT("Owning Character Cast Fail"));
}

void UShopComponent::InitShop()
{
	CurrentItems = ShopItems;
}

void UShopComponent::Sell(const int32 Index)
{
	if (CurrentItems[Index].InitAmount <= 0) return;
	if (OwningCharacter->Pay(CurrentItems[Index].Cost))
	{
		OwningCharacter->ReceiveShopItem(CurrentItems[Index]);
		CurrentItems[Index].InitAmount--;
	}
}

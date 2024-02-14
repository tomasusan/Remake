// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/MainUserWidget.h"
#include "FPGCharacter.h"
#include "FPGGameInstance.h"

FBasicInteractableItemInfo UMainUserWidget::GetDetectedItemInfo()
{
	const auto PlayerCharacterController = GetOwningPlayer();
	const auto PlayerCharacter = Cast<AFPGCharacter>(PlayerCharacterController->GetPawn());
	checkf(PlayerCharacter, TEXT("MainUserWidget casting owning player to AFPGCharacter failed"));

	return PlayerCharacter->ReportDetectedItemInfo();
}

void UMainUserWidget::GetCurrentItems(TArray<FBasicInteractableItemInfo>& Items)
{
	const auto PlayerCharacterController = GetOwningPlayer();
	const auto PlayerCharacter = Cast<AFPGCharacter>(PlayerCharacterController->GetPawn());
	checkf(PlayerCharacter, TEXT("MainUserWidget casting owning player to AFPGCharacter failed"));

	Items = PlayerCharacter->GetItems();
}

void UMainUserWidget::GetItemsByType(TArray<FBasicInteractableItemInfo>& Items, const EItemType Type)
{
	const auto PlayerCharacterController = GetOwningPlayer();
	const auto PlayerCharacter = Cast<AFPGCharacter>(PlayerCharacterController->GetPawn());
	checkf(PlayerCharacter, TEXT("MainUserWidget casting owning player to AFPGCharacter failed"));

	Items = PlayerCharacter->GetItemsByType(Type);
}

void UMainUserWidget::GetShopItems(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo)
{
	const auto CurrentActiveShop = Cast<UFPGGameInstance>(GetGameInstance())->GetCurrentActiveShop();
	CurrentActiveShop->GetShopItems(Items, ShopItemInfo);
}


void UMainUserWidget::GetShopItemsByType(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo, const EItemType Type)
{
	const auto CurrentActiveShop = Cast<UFPGGameInstance>(GetGameInstance())->GetCurrentActiveShop();
	CurrentActiveShop->GetShopItemsByType(Items, ShopItemInfo, Type);
}

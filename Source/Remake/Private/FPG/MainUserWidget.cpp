// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/MainUserWidget.h"
#include "FPGCharacter.h"

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

void UMainUserWidget::GetItemsByType(TArray<FBasicInteractableItemInfo>& Items,const EItemType Type)
{
	const auto PlayerCharacterController = GetOwningPlayer();
	const auto PlayerCharacter = Cast<AFPGCharacter>(PlayerCharacterController->GetPawn());
	checkf(PlayerCharacter, TEXT("MainUserWidget casting owning player to AFPGCharacter failed"));

	Items = PlayerCharacter->GetItemsByType(Type);
}

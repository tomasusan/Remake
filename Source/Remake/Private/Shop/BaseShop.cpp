// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/BaseShop.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ShopComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseShopLog, All, All);

// Sets default values
ABaseShop::ABaseShop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShopRepositoryComponent = CreateDefaultSubobject<UShopComponent>("ShopRepositoryComponent");
}

void ABaseShop::GetShopItems(TArray<FBasicInteractableItemInfo>& Items,
                             TArray<FShopItemData>& ShopItemInfo)
{
	ShopRepositoryComponent->GetItems(Items, ShopItemInfo);
}

void ABaseShop::GetShopItemsByType(TArray<FBasicInteractableItemInfo>& Items,
                                   TArray<FShopItemData>& ShopItemInfo, EItemType Type)
{
	ShopRepositoryComponent->GetItemByType(Items, ShopItemInfo, Type);
}

void ABaseShop::Detected()
{
	Super::Detected();
	UE_LOG(BaseShopLog, Warning, TEXT("Shop Detected"));
	PlayAnimationFadeIn();
}

void ABaseShop::LoseDetected()
{
	Super::LoseDetected();
	UE_LOG(BaseShopLog, Warning, TEXT("Shop Lose Detected"));
	PlayAnimationFadeOut();
}

void ABaseShop::AddFavourite(FShopItemData NewFavourite)
{
	ShopRepositoryComponent->AddFavourite(NewFavourite);
}

void ABaseShop::RemoveFavourite(FShopItemData RemovedFavourite)
{
	ShopRepositoryComponent->RemoveFavourite(RemovedFavourite);
}

void ABaseShop::Sell(FShopItemData SoldItemInfo)
{
	ShopRepositoryComponent->Sell(SoldItemInfo);
}

// Called when the game starts or when spawned
void ABaseShop::BeginPlay()
{
	Super::BeginPlay();
}

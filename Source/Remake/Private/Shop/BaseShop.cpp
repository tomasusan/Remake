// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/BaseShop.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ShopComponent.h"

// Sets default values
ABaseShop::ABaseShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	ShopStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("ShopMesh");
	ShopStaticMesh->SetupAttachment(GetRootComponent());

	ShopRepositoryComponent = CreateDefaultSubobject<UShopComponent>("ShopRepositoryComponent");
}

// Called when the game starts or when spawned
void ABaseShop::BeginPlay()
{
	Super::BeginPlay();
	
}
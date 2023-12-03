#include "BasePickActor.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BasePickActorLog, All, All);

ABasePickActor::ABasePickActor()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ABasePickActor::BeginPlay()
{
	Super::BeginPlay();

	const auto Row = DataTable->FindRow<FPickItemData>(ItemName, FString("PickData"), true);
	ItemData = *Row;
	UE_LOG(BasePickActorLog, Display, TEXT("\nItemName:%s,ItemMaxAmount:%d"), *ItemData.ItemName.ToString(), ItemData.MaxAmount);
}

void ABasePickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


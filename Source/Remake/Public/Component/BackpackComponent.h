#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RemakeCoreTypes.h"
#include "BackpackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMAKE_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBackpackComponent();

	void PickItem(const FPickItemData& ItemData);
	void ReceiveShopItem(const FShopItemData& ShopItemData);
	void UseItem(const int32 Index);
	void ThrowItem(const int32 Index);
	void SwitchBackpackOpen();
	TArray<FPickItemData> GetBackpack() const {return Items;}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> BackpackWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	UDataTable* ItemDataTable;
private:
	TArray<FPickItemData> Items;

	bool bBackpackOpen = false;
};

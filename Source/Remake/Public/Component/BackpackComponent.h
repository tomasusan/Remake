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

	void PickItem(FPickItemData ItemData);
	void UseItem();
	void ThrowItem();
	void SwitchBackpackOpen();
	TArray<FPickItemData> GetBackpack() const {return Items;}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> BackpackWidgetClass;
private:
	TArray<FPickItemData> Items;

	bool bBackpackOpen = false;
};

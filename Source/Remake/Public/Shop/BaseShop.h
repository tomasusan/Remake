// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractableActor.h"
#include "GameFramework/Actor.h"
#include "RemakeCoreTypes.h"
#include "BaseShop.generated.h"

class UBackpackComponent;
class UStaticMeshComponent;
class USceneComponent;
class UShopComponent;

UCLASS()
class REMAKE_API ABaseShop : public ABaseInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseShop();

	UFUNCTION(BlueprintCallable)
	void GetShopItems(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo);

	UFUNCTION(BlueprintCallable)
	void GetShopItemsByType(TArray<FBasicInteractableItemInfo>& Items, TArray<FShopItemData>& ShopItemInfo, EItemType Type);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimationFadeIn();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimationFadeOut();

	UFUNCTION(BlueprintCallable)
	virtual void Detected() override;

	UFUNCTION(BlueprintCallable)
	virtual void LoseDetected() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UShopComponent* ShopRepositoryComponent;
	
};

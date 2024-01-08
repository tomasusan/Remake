// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseShop.generated.h"

class UBackpackComponent;
class UStaticMeshComponent;
class USceneComponent;
class UShopComponent;

UCLASS()
class REMAKE_API ABaseShop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UStaticMeshComponent* ShopStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UShopComponent* ShopRepositoryComponent;
	
};

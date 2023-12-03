// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "RemakeCoreTypes.h"
#include "BasePickActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class REMAKE_API ABasePickActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickActor();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	UDataTable* DataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	FName ItemName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* WeaponMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FPickItemData ItemData;
};

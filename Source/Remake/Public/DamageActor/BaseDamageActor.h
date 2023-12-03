// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDamageActor.generated.h"

UCLASS()
class REMAKE_API ABaseDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageInfo")
	float Radius = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageInfo")
	FColor SphereColor = FColor::Black;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageInfo")
	float Damage = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageInfo")
	TSubclassOf<UDamageType> DamageType;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	

};

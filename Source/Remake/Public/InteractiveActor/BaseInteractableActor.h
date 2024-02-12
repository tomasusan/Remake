// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RemakeCoreTypes.h"
#include "BaseInteractableActor.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class REMAKE_API ABaseInteractableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Compnent")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UStaticMeshComponent* InteractableActorMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Detected();
	virtual void LoseDetected();

	UFUNCTION(BlueprintCallable)
	FBasicInteractableItemInfo GetBasicInfo() const { return BasicInfo; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InteractableActorInfo")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InteractableActorInfo")
	UDataTable* BasicDataTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InteractableActorInfo")
	bool bDetectable = true;

private:
	FBasicInteractableItemInfo BasicInfo;
	void InitActorInfo();
};

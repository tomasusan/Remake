// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPGTransformActor.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class REMAKE_API AFPGTransformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPGTransformActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Comopnent")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UStaticMeshComponent* HighlightMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Material")
	UMaterialInterface* HighlightMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnDetected();
	void ShowHighlight();
	void HideHighlight();
};

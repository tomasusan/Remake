// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPGTransformActor.generated.h"

class USphereComponent;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	USphereComponent* TestingSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	USphereComponent* CollisionSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DetectInfo")
	float BasicDistance = 150;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DetectInfo")
	float Frequency = 0.03;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnDetected();
	void ShowHighlight();
	void HideHighlight();
	void UpdateLocation(FTransform NewTransform);
	bool IsInCollision() const;
	void StartTest(AActor* OwningActor, FVector InitLocation, FVector InitScale, FVector InitDirection,
	               float InitDistance);
	void StopTest();
	void OnTest();
	bool GetTestSphereState() const { return TestSphereOverlap; }
	UFUNCTION(BlueprintCallable)
	void SetTestSphereBeginOverlap() { TestSphereOverlap = true; };
	UFUNCTION(BlueprintCallable)
	void SetTestSphereEndOverlap() { TestSphereOverlap = false; };

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap();

	UFUNCTION(BlueprintImplementableEvent)
	void SetSimulation();

	UFUNCTION(BlueprintCallable)
	void AssembleAllComponent();

	void SetCanShowHighlight(const bool bCanShowHighlight);

private:
	bool bUpdateLocation = false;

	float TestDistance;
	float TestStep = 10;
	float TestSphereRateStaticMesh;
	float TestSphereRateCollision;
	float TestSphereRateHighlight;
	//FVector InitScale;
	FVector BeginScale;
	FVector OwningActorLocation;
	FVector TestLocation;
	FVector TestDirection;
	FVector TransformScaleRate;
	bool CanTransform = true;
	bool TestSphereOverlap = false;
	bool CanShowHighlight = true;
	FTimerHandle TestTimerHandle;
	FTimerHandle Delay;
};

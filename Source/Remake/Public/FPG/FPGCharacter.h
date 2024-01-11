// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Serialization/ArchiveReplaceObjectRef.h"
#include "FPGCharacter.generated.h"

class UCameraComponent;
class AFPGTransformActor;

UCLASS()
class REMAKE_API AFPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DetectInfo")
	float TraceDetectDistance = 100.0f;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(const float Val);
	void MoveRight(const float Val);
	void LookUp(float Val);
	void LookRight(float Val);
	AFPGTransformActor* DetectActor();
	void OnStartHold();
	void OnStopHold();
	
	UPROPERTY()
	AFPGTransformActor* LastDetectActor = nullptr;

	UPROPERTY()
	AFPGTransformActor* CurrentDetectActor = nullptr;

	bool bHolding = false;
	float Distance = 0.0f;

	FTransform LastTransform;
	FTransform DesiredTransform;
};

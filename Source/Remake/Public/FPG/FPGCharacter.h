// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RemakeCoreTypes.h"
#include "FPGCharacter.generated.h"

class UBackpackComponent;
class ABaseInteractableActor;
class UCameraComponent;
class AFPGTransformActor;

DECLARE_MULTICAST_DELEGATE(FShowDetectedItemInfoSigniture);
DECLARE_MULTICAST_DELEGATE(FHideDetectedItemInfoSigniture);
DECLARE_MULTICAST_DELEGATE(FUpdateHintInfoSignature);
DECLARE_MULTICAST_DELEGATE(FOpenShopSignature)

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UBackpackComponent* BackpackComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DetectInfo")
	float TraceDetectDistance = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Component")
	UStaticMeshComponent* Sphere;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Detect", meta=(EditCondition="!bDetectTransformActor"))
	bool bDetectInteractiveActor = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Detect", meta=(EditCondition="!bDetectInteractiveActor"))
	bool bDetectTransformActor = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CameraShake")
	bool bCameraShack = true;

	TArray<FBasicInteractableItemInfo> GetItems() const;
	TArray<FBasicInteractableItemInfo> GetItemsByType(const EItemType Type) const;

	FBasicInteractableItemInfo ReportDetectedItemInfo();

	FShowDetectedItemInfoSigniture OnShowDetectedItemInfo;
	FHideDetectedItemInfoSigniture OnHideDetectedItemInfo;
	FUpdateHintInfoSignature OnUpdateHintInfo;
	FOpenShopSignature OnOpenShop;

private:
	void MoveForward(const float Val);
	void MoveRight(const float Val);
	void LookUp(float Val);
	void LookRight(float Val);
	void Pick();
	void OpenShopWidget();
	ABaseInteractableActor* DetectInteractableActor() const;
	AFPGTransformActor* DetectTransformActor() const;
	void OnStartHoldTransform();
	void OnStopHoldTransform();
	void HandleDetectInteractableActor();
	void HandleDetectTransformActor();
	void SwitchWidget();
	void StartCameraShake();
	void CameraShake();

	UPROPERTY()
	AFPGTransformActor* LastDetectTransformActor = nullptr;

	UPROPERTY()
	AFPGTransformActor* CurrentDetectTransformActor = nullptr;

	UPROPERTY()
	ABaseInteractableActor* LastDetectInteractableActor = nullptr;

	UPROPERTY()
	ABaseInteractableActor* CurrentDetectInteractableActor = nullptr;

	bool bHolding = false;
	bool bEnableLookAround = true;
	float Distance = 0.0f;

	FTransform LastTransform;
	FTransform DesiredTransform;
	FTransform InitCameraTransform;

	FTimerHandle CameraShakeTimerHandle;
};

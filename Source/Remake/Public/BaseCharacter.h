// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UWeaponComponent;
class UTextRenderComponent;
class USpringArmComponent;
class UCameraComponent;
class UBaseCharacterMovementComponent;
class UHealthComponent;
class UBackpackComponent;

DECLARE_MULTICAST_DELEGATE(FOnReloadSignature);

UCLASS()
class REMAKE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable)
	bool IsSprinting() const;

	UFUNCTION(BlueprintCallable)
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable)
	void Land();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	bool bWantJump = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Name")
	FName CharacterName;
	
	void Offset(float PitchOffset, float YawOffset);

	FOnReloadSignature OnReloadHandle;
	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBackpackComponent* BackpackComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FallDamage")
	FVector2D FallDamageVelocity = FVector2D(900, 1200);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FallDamage")
	FVector2D FallDamage = FVector2D(10, 100);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private://for function
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void LookUp(float Amount);
	void LookRight(float Amount);
	void OnStartSprint();
	void OnStopSprint();
	void OnJump();
	void OnDeath();
	void Fire();
	void OnHealthChange(float Health) const;
	
	bool WantSprint = false;
	bool IsMovingForward = false;
	bool bCanMove = true;
	
	UFUNCTION()
	void OnLand(const FHitResult& Hit);

};

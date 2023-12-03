// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FRifleOffsetSignature, float, float);

UCLASS()
class REMAKE_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()
public:
	ARifleWeapon();

	virtual void MakeShot() override;
	virtual void StartFire() override;;
	virtual void StopFire() override;
	virtual void MakeDamage(const FHitResult& HitResult, APlayerController* Controller) override;
	virtual void GetFinalOffset(float& PitchOffset, float& YawOffset);

	FRifleOffsetSignature RifleOffsetHandle;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoFire")
	FRifleInfo RifleInfo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	TMap<FName, float> DamageMap;

private:
	FVector2D PitchOffsetInputRange = FVector2D(0, 100);
	FVector2D YawOffsetInputRange = FVector2D(0, 100);
	FVector2D PitchOffsetOutputRange = FVector2D(0, 1);
	FVector2D YawOffsetOutputRange = FVector2D(0, 1);

	int i=1;
	int j=2;
};

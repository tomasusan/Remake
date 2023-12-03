// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RifleWeapon.h"
#include "BaseCharacter.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY_STATIC(RifleWeaponLog, All, All);

ARifleWeapon::ARifleWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARifleWeapon::MakeShot()
{
	Super::MakeShot();
	
	if(!GetWorld()) return;
	if(IsAmmoEmpty())
	{
		UE_LOG(RifleWeaponLog, Warning, TEXT("Ammo empty!"));
		return;
	}
	if(IsClipEmpty())
	{
		UE_LOG(RifleWeaponLog, Warning, TEXT("Clip Empty!"));
		const auto Character = Cast<ABaseCharacter>(GetOwner());
		if(!Character) return;
		StopFire();
		Character->OnReloadHandle.Broadcast();
		return;
	}

	AmmoInfo.AmmoInClip--;
	UE_LOG(RifleWeaponLog, Warning, TEXT("Ammo: %d/%d"), AmmoInfo.AmmoInClip, AmmoInfo.CurrentAmmo);

	const auto Controller = GetPlayerController();

	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return;

	const FVector SocketLocation = GetMuzzleLocation();
	FVector TraceStart;
	FVector TraceEnd;
	if(!GetTraceInfo(TraceStart, TraceEnd)) return;

	if(RifleInfo.bOffset)
	{
		//UE_LOG(RifleWeaponLog, Warning, TEXT("Now Offsetting"));
		float PitchOffset;
		float YawOffset;
		GetFinalOffset(PitchOffset, YawOffset);
		//UE_LOG(RifleWeaponLog, Error, TEXT("PitchOffset: %f, YawOffset: %f"), PitchOffset, YawOffset);
		RifleOffsetHandle.Broadcast(PitchOffset, YawOffset);
	}
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if(HitResult.bBlockingHit)
	{
		
		MakeDamage(HitResult, Controller);
	}
	DrawDebugLine(GetWorld(), SocketLocation, HitResult.bBlockingHit ?HitResult.Location : TraceEnd, FColor::Red, false, 3, 0, 3);

	
	
}

void ARifleWeapon::StartFire()
{
	MakeShot();
	GetWorld()->GetTimerManager().SetTimer(RifleInfo.AutoFireTimerHandle, this, &ARifleWeapon::MakeShot, RifleInfo.ShootFrequency, true);
}

void ARifleWeapon::StopFire()
{
	Super::StopFire();
	if(GetWorld()->GetTimerManager().TimerExists(RifleInfo.AutoFireTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(RifleInfo.AutoFireTimerHandle);
	}
}

void ARifleWeapon::MakeDamage(const FHitResult& HitResult, APlayerController* Controller)
{
	if(HitResult.GetActor()->IsA<ABaseCharacter>())
	{
		const auto HitActor = Cast<ABaseCharacter>(HitResult.GetActor());
		if(HitActor == GetOwner()) return; 
		//UE_LOG(RifleWeaponLog, Warning, TEXT("%s"),*HitActor->GetName());
		const auto BoneName = HitResult.BoneName;
		//UE_LOG(RifleWeaponLog, Warning, TEXT("%s"), *BoneName.ToString());
		if(DamageMap.Find(BoneName))
		{
			HitActor->TakeDamage(DamageMap[BoneName], FDamageEvent{}, Controller, this);
		}
		else
		{
			HitActor->TakeDamage(DamageAmount, FDamageEvent{}, Controller, this);
		}
	}
	
}

void ARifleWeapon::GetFinalOffset(float& PitchOffset, float& YawOffset)
{
	const auto PitchClamp = FMath::GetMappedRangeValueClamped(PitchOffsetInputRange, PitchOffsetOutputRange, RifleInfo.PitchOffset);
	const auto YawClamp = FMath::GetMappedRangeValueClamped(YawOffsetInputRange, YawOffsetOutputRange, RifleInfo.YawOffset);
	PitchOffset = -FMath::RandRange(0.0, PitchClamp);
	YawOffset = FMath::RandRange(-YawClamp, YawClamp);
}

void ARifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

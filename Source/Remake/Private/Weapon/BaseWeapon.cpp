#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "BaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

ABaseWeapon::ABaseWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ABaseWeapon::MakeShot()
{
	
}

APlayerController* ABaseWeapon::GetPlayerController() const
{
	const auto Character = Cast<ABaseCharacter>(GetOwner());
	if(!Character) return nullptr;

	return Cast<APlayerController>(Character->GetController());
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewPoint, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) return false;

	Controller->GetPlayerViewPoint(ViewPoint, ViewRotation);
	return true;
}

FVector ABaseWeapon::GetMuzzleLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocket);
}

bool ABaseWeapon::GetTraceInfo(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

bool ABaseWeapon::CanReload() const
{
	return AmmoInfo.AmmoInClip != AmmoInfo.ClipCapacity;
}

void ABaseWeapon::Reload()
{
	if(AmmoInfo.AmmoInClip == AmmoInfo.ClipCapacity) return;

	StopFire();
	int32 GetAmmoAmount;

	if(AmmoInfo.CurrentAmmo < AmmoInfo.ClipCapacity - AmmoInfo.AmmoInClip)
	{
		GetAmmoAmount = AmmoInfo.CurrentAmmo;
		AmmoInfo.CurrentAmmo = 0;
	}
	else
	{
		GetAmmoAmount = AmmoInfo.ClipCapacity - AmmoInfo.AmmoInClip;
		AmmoInfo.CurrentAmmo -= GetAmmoAmount;
	}
	
	AmmoInfo.AmmoInClip += GetAmmoAmount;
}

void ABaseWeapon::MakeHit(FHitResult& HitResult,const FVector& TraceStart,const FVector& TraceEnd) const
{
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	
}

void ABaseWeapon::MakeDamage(const FHitResult& HitResult, APlayerController* Controller)
{
}

void ABaseWeapon::Fire()
{
	MakeShot();
}

void ABaseWeapon::StartFire()
{
	
}

void ABaseWeapon::StopFire()
{
	
}


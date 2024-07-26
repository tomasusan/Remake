#include "Component/WeaponComponent.h"

#include "AnimUtils.h"
#include "BaseCharacter.h"
#include "BaseWeapon.h"
#include "RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "ReloadFinishAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(WeaponComponentLog, All, All);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	AnimInit();
}

void UWeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;
	CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	if(!CurrentWeapon) return;
	if(const auto Character = Cast<ABaseCharacter>(GetOwner()))
	{
		if(CurrentWeapon->IsA<ARifleWeapon>())
		{
			UE_LOG(WeaponComponentLog, Display,TEXT("Is A Rifle"));
			auto Rifle = Cast<ARifleWeapon, ABaseWeapon>(CurrentWeapon);
			Rifle->RifleOffsetHandle.AddUObject(Character, &ABaseCharacter::Offset);
			ReLoadHandle.AddUObject(Rifle, &ABaseWeapon::Reload);
		}
		const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, SocketName);
		CurrentWeapon->SetOwner(Character);
	}
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
	if(const auto Character = Cast<ABaseCharacter>(GetOwner()))
	{
		Character->PlayAnimMontage(AnimMontage);
	}
}

void UWeaponComponent::Fire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->Fire();
}

void UWeaponComponent::StartFire()
{
	if(!CurrentWeapon) return;
	if(!CanFire())
	{
		UE_LOG(WeaponComponentLog, Error, TEXT("Cant Fire"));
		return;
	}
	CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void UWeaponComponent::SetCanFire(bool Ability)
{
	bCanFire = Ability;
}

void UWeaponComponent::AnimInit()
{
	if(!CurrentWeapon) return;
	const auto ReloadAnim = CurrentWeapon->ReloadAnim;
	if(!ReloadAnim) return;

	const auto ReloadFinishNotify = AnimUtils::FindNotifyByClass<UReloadFinishAnimNotify>(ReloadAnim);
	if(ReloadFinishNotify)
	{
		ReloadFinishNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinish);
	}
}

void UWeaponComponent::OnReloadFinish()
{
	UE_LOG(WeaponComponentLog, Display, TEXT("Finish Reload"));
	bInReloadAnimProgress = false;
}

void UWeaponComponent::OnReload()
{
	if(!CanReload()) return;
	UE_LOG(WeaponComponentLog, Display, TEXT("Now Reaload"));
	const auto ReloadAnim = CurrentWeapon->ReloadAnim;
	if(!ReloadAnim)
	{
		UE_LOG(WeaponComponentLog, Error, TEXT("No AnimMontage Found"));
		return;
	}
	
	UE_LOG(WeaponComponentLog, Error, TEXT("%s"), *ReloadAnim->GetName());
	bInReloadAnimProgress = true;
	PlayAnimMontage(ReloadAnim);
	ReLoadHandle.Broadcast();
}

bool UWeaponComponent::CanFire() const
{
	return !bInReloadAnimProgress && bCanFire;
}

bool UWeaponComponent::CanReload() const
{
	return !bInReloadAnimProgress && CurrentWeapon->CanReload();
}
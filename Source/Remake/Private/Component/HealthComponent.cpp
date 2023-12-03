
#include "HealthComponent.h"
#include "FireDamageType.h"
#include "IceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0, MaxHealth);
	OnHealthChangeHandle.Broadcast(Health);
	return;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	OnHealthChangeHandle.Broadcast(Health);

	if(AActor* ComponentOwner = GetOwner())
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
	}
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(BIsDead()) return;

	UE_LOG(HealthComponentLog, Error, TEXT("Now Taking Damage"));
	SetHealth(Health - Damage);
	if(BIsDead())
	{
		OnDeathHandle.Broadcast();
		return;
	}
	else if(bAutoHeal && GetWorld())
	{
		if(GetWorld()->GetTimerManager().TimerExists(HealTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
		}
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UHealthComponent::Heal, HealUpdateTime, true, HealDelay);
	}
	
	if(DamageType)
	{
		if(DamageType->IsA<UFireDamageType>())
		{
			UE_LOG(HealthComponentLog, Warning, TEXT("On Fire Damage"));
		}
		else if(DamageType->IsA<UIceDamageType>())
		{
			UE_LOG(HealthComponentLog, Warning, TEXT("On Ice Damage"));
		}
	}
}

void UHealthComponent::Heal()
{
	if(FMath::IsNearlyEqual(Health, MaxHealth))
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
	SetHealth(Health + HealModifier);
}
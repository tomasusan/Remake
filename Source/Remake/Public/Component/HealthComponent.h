// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSigniture)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSigniture, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMAKE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION()
	float GetHealth() const {return Health;}
	
	UFUNCTION()
	bool BIsDead() const {return FMath::IsNearlyZero(Health);}
	

	void SetHealth(float NewHealth);
	
	FOnDeathSigniture OnDeathHandle;
	FOnHealthChangeSigniture OnHealthChangeHandle;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal")
	bool bAutoHeal = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",  meta = (EditCondition = "bAutoHeal"))
	float HealUpdateTime = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",  meta = (EditCondition = "bAutoHeal"))
	float HealDelay = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",  meta = (EditCondition = "bAutoHeal"))
	float HealModifier = 5;
	
private:
	UFUNCTION()
	void OnTakeAnyDamageHandle(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser);
	void Heal();
	
	float Health = 0;

	
	FTimerHandle HealTimerHandle;
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

DECLARE_MULTICAST_DELEGATE(FRelaodSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMAKE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	
	void OnReload();

	void Fire();
	void StartFire();
	void StopFire();
	ABaseWeapon* GetCurrentWeapon() const {return CurrentWeapon;}

	FRelaodSignature ReLoadHandle;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName SocketName;

private:
	void SpawnWeapon();

	void PlayAnimMontage(UAnimMontage* AnimMontage) const;
	void AnimInit();
	void OnReloadFinish();
	bool CanFire() const;
	bool CanReload() const;
	bool bInReloadAnimProgress = false;
	
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;
};

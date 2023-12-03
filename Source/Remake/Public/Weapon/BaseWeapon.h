#pragma once

#include "CoreMinimal.h"
#include "RemakeCoreTypes.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;


UCLASS()
class REMAKE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void Fire();
	virtual void StartFire();
	virtual void StopFire();
	virtual void MakeShot();
	virtual void MakeDamage(const FHitResult& HitResult, APlayerController* Controller);
	
	bool IsClipEmpty() const {return AmmoInfo.AmmoInClip == 0;}
	bool IsAmmoEmpty() const {return AmmoInfo.CurrentAmmo == 0 && IsClipEmpty();}
	bool CanReload() const;

	virtual void Reload();
	
	void MakeHit(FHitResult& HitResult,const FVector& TraceStart,const FVector& TraceEnd) const;
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewPoint, FRotator& ViewRotation) const;
	FVector GetMuzzleLocation() const;
	bool GetTraceInfo(FVector& TraceStart, FVector& TraceEnd) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	FAmmoInfo AmmoInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* ReloadAnim;

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Socket")
	FName MuzzleSocket = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim")
	int32 TraceMaxDistance = 3000;

private:

	FTimerHandle StartTimerHandle;
};

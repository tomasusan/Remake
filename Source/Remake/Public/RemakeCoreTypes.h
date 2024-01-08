#pragma once
#include "Engine/DataTable.h"
#include "RemakeCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FRifleInfo
{
	GENERATED_USTRUCT_BODY()
	;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoFire")
	bool bAutoFire = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoFire", meta = (EditCondition = "bAutoFire"))
	float ShootFrequency = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Offset")
	bool bOffset = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Offset",
		meta = (EditCondition = "bOffset", ClampMin = "0", ClampMax = "100"))
	float PitchOffset = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Offset",
		meta = (EditCondition = "bOffset", ClampMin = "0", ClampMax = "100"))
	float YawOffset = 0;

	FTimerHandle AutoFireTimerHandle;
};

USTRUCT(BlueprintType)
struct FAmmoInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 MaxAmmo = 180;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 CurrentAmmo = 180;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 ClipCapacity = 30;

	int32 AmmoInClip = 0;
};

USTRUCT(BlueprintType)
struct FPickItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	int32 MaxAmount = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	int32 CurrentAmount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	UTexture2D* Texture;

};

USTRUCT(BlueprintType)
struct FShopItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ShopItem")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ShopItem")
	int32 InitAmount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ShopItem")
	bool Update = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ShopItem")
	UTexture2D* Texture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ShopItem")
	int32 Cost = 0;
};

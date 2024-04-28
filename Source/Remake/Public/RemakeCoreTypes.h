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

UENUM(BlueprintType)
enum class EItemType:uint8
{
	Weapon,
	Consumable,
	Buff,
	Tool
};


USTRUCT(BlueprintType)
struct FBasicInteractableItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BasicInfo")
	FName ItemName = "Name Error";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BasicInfo")
	EItemType Type = EItemType::Consumable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BasicInfo")
	FText ItemDescription = FText::FromString(FString("Description Error"));

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Icon")
	UTexture2D* ItemTexture = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Icon")
	UTexture2D* ItemTextureBackpack = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="DetectionInfo")
	bool bDetectable = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="DetectionInfo", meta=(EditCondition="bDetectable"))
	bool bShowHint = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="DetectionInfo", meta=(EditCondition="bDetectable"))
	bool bPickable = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="DetectionInfo", meta=(EditCondition="bPickable"))
	bool bCanOverlay = true;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="InBackpackInfo")
	int32 CurrentAmount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="InBackpackInfo", meta=(EditCondition="bCanOverlay&&bPickable&&bDetectable"))
	int32 MaxAmount = 99;
};

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentHP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHP = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentMP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxMP = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentMoney = 500;
};

//deprecated structure
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

//deprecated structure
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
	UTexture2D* ShopTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ShopItem")
	int32 Cost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ShopItem")
	bool bFavourite = false;

	bool operator==(const FShopItemData& AnotherShopItem) const
	{
		return ItemName == AnotherShopItem.ItemName;
	}
};


USTRUCT(BlueprintType)
struct FMyStruct: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Val1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Val2;
};

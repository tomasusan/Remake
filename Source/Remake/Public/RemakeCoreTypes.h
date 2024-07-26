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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="InBackpackInfo",
		meta=(EditCondition="bCanOverlay&&bPickable&&bDetectable"))
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


UCLASS(BlueprintType)
class UTime : public UObject
{
	GENERATED_BODY()

	int32 Min;
	int32 Sec;
	int32 Ms;

public:
	static UTime* CreateTime(int32 m, int32 s, int32 ms)
	{
		UTime* NewTime = NewObject<UTime>();
		NewTime->Set(m, s, ms);
		return NewTime;
	}

	UFUNCTION(BlueprintCallable)
	void Set(int32 m, int32 s, int32 ms)
	{
		Min = m;
		Sec = s;
		Ms = ms;
	}

	UFUNCTION(BlueprintCallable)
	FString ToString() const
	{
		FString St_Min = "0";
		if (Min < 10) St_Min += FString::FromInt(Min);
		else St_Min = FString::FromInt(Min);

		FString St_Sec = "0";
		if (Sec < 10) St_Sec += FString::FromInt(Sec);
		else St_Sec = FString::FromInt(Sec);

		FString St_Ms = "1000";
		if (Ms < 1000 && Ms >= 100) St_Ms = "0" + FString::FromInt(Ms);
		else if (Ms < 100 && Ms >= 10) St_Ms = "00" + FString::FromInt(Ms);
		else if (Ms < 10 && Ms >= 0) St_Ms = "000" + FString::FromInt(Ms);

		return St_Min + ":" + St_Sec + ":" + St_Ms;
	}

	UFUNCTION(BlueprintCallable)
	void TimeDown(int32 ms)
	{
		Ms -= ms;

		while (Ms < 0)
		{
			Sec--;
			Ms += 1000;
		}

		while (Sec < 0)
		{
			Min--;
			Sec += 60;
		}

		if (Min < 0)
		{
			Ms = 0;
			Sec = 0;
			Min = 0;
		}
	}

	UFUNCTION(BlueprintCallable)
	bool IsZero() const
	{
		return Ms == 0 && Min == 0 && Sec == 0;
	}
};

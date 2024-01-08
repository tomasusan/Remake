#include "BaseCharacter.h"

#include "BaseWeapon.h"
#include "Component/BaseCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "WeaponComponent.h"
#include "AnimUtils.h"
#include "BackpackComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRenderComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>("BackpackComponent");
}

void ABaseCharacter::Offset(float PitchOffset, float YawOffset)
{
	AddControllerPitchInput(PitchOffset);
	AddControllerYawInput(YawOffset);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChange(HealthComponent->GetHealth());
	HealthComponent->OnDeathHandle.AddUObject(this, &ABaseCharacter::OnDeath);
	HealthComponent->OnHealthChangeHandle.AddUObject(this, &ABaseCharacter::OnHealthChange);

	LandedDelegate.AddDynamic(this, &ABaseCharacter::OnLand);
	OnReloadHandle.AddUObject(WeaponComponent, &UWeaponComponent::OnReload);

	SetToken(100);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetMovementComponent()->IsFalling())
	{
		bCanMove = false;
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &ABaseCharacter::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::OnJump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::OnStartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::OnStopSprint);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::OnReload);
}


void ABaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0;
	if (bCanMove)
		AddMovementInput(GetActorForwardVector(), Amount);
}

void ABaseCharacter::MoveRight(float Amount)
{
	if (bCanMove)
		AddMovementInput(GetActorRightVector(), Amount);
}

void ABaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void ABaseCharacter::LookRight(float Amount)
{
	AddControllerYawInput(Amount);
}

void ABaseCharacter::OnStartSprint()
{
	WantSprint = true;
}

void ABaseCharacter::OnStopSprint()
{
	WantSprint = false;
}

bool ABaseCharacter::IsSprinting() const
{
	return WantSprint && IsMovingForward && !GetVelocity().IsZero();
}

float ABaseCharacter::GetMovementDirection() const
{
	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const FVector VectorForward = GetActorForwardVector();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(VelocityNormal, VectorForward));
	const auto Cross = FVector::CrossProduct(VelocityNormal, VectorForward);
	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(Cross.Z);
}

void ABaseCharacter::OnJump()
{
	if (!bCanMove) return;
	Super::Jump();
	bWantJump = true;
	bCanMove = false;
}

void ABaseCharacter::Land()
{
	bWantJump = false;
	bCanMove = true;
}

void ABaseCharacter::OnDeath()
{
	if (!DeathAnim) return;

	PlayAnimMontage(DeathAnim);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}


	//GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ABaseCharacter::Fire()
{
}


void ABaseCharacter::OnHealthChange(float Health) const
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ABaseCharacter::GainToken(const int32 GainingAmount)
{
	CurrentToken = FMath::Clamp(CurrentToken + GainingAmount, CurrentToken, MaxToken);
}

bool ABaseCharacter::Pay(const int32 Cost)
{
	bool Success = true;
	if (CurrentToken - Cost < 0) Success = false;
	else
	{
		CurrentToken -= Cost;
	}
	return Success;
}

void ABaseCharacter::ReceiveShopItem(const FShopItemData& ShopItemData)
{
	BackpackComponent->ReceiveShopItem(ShopItemData);
}


void ABaseCharacter::OnLand(const FHitResult& Hit)
{
	const auto FallVelocityZ = FMath::Abs(GetCharacterMovement()->Velocity.Z);

	if (FallVelocityZ < FallDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(FallDamageVelocity, FallDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, this);
}

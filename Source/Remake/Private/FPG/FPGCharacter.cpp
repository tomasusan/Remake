// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/FPGCharacter.h"
#include "FPGTransformActor.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(FPGCharacter, All, All);

// Sets default values
AFPGCharacter::AFPGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFPGCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto DetectedActor = DetectActor();
	if (DetectedActor)
	{
		CurrentDetectActor = DetectedActor;
		if (DetectedActor != LastDetectActor)
		{
			if (LastDetectActor)
				LastDetectActor->HideHighlight();
				LastDetectActor = DetectedActor;
			DetectedActor->OnDetected();
		}
		if (bHolding && CurrentDetectActor)
		{
			FVector ViewLocation;
			FRotator ViewRotation;
			GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

			const auto DetectedActorDirection = ViewRotation.Vector();
			DesiredTransform = CurrentDetectActor->GetActorTransform();
			LastTransform = CurrentDetectActor->GetActorTransform();
			
			const FVector NewDetectedActorLocation = ViewLocation + DetectedActorDirection * Distance;
			DesiredTransform.SetLocation(NewDetectedActorLocation);
			CurrentDetectActor->UpdateLocation(DesiredTransform);

			if (CurrentDetectActor->IsInCollision())
				CurrentDetectActor->UpdateLocation(LastTransform);
		}
	}
	else
	{
		if (LastDetectActor)
		{
			LastDetectActor->HideHighlight();
			LastDetectActor = nullptr;
		}
		CurrentDetectActor = nullptr;
		bHolding = false;
	}
}

// Called to bind functionality to input
void AFPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AFPGCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AFPGCharacter::MoveRight);
		PlayerInputComponent->BindAxis("LookUp", this, &AFPGCharacter::LookUp);
		PlayerInputComponent->BindAxis("LookRight", this, &AFPGCharacter::LookRight);
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPGCharacter::OnStartHold);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPGCharacter::OnStopHold);
	}
}

void AFPGCharacter::MoveForward(const float Val)
{
	AddMovementInput(GetActorForwardVector(), Val);
}

void AFPGCharacter::MoveRight(const float Val)
{
	AddMovementInput(GetActorRightVector(), Val);
}

void AFPGCharacter::LookUp(float Val)
{
	AddControllerPitchInput(Val);
}

void AFPGCharacter::LookRight(float Val)
{
	AddControllerYawInput(Val);
}

AFPGTransformActor* AFPGCharacter::DetectActor()
{
	FVector ViewLocation;
	FRotator ViewRotator;
	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotator);

	const FVector TraceStart = ViewLocation;
	const FVector TraceDirection = ViewRotator.Vector();

	FVector TraceEnd = TraceStart + TraceDirection * TraceDetectDistance;


	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		auto DetectedActor = HitResult.GetActor();
		if (DetectedActor->IsA<AFPGTransformActor>())
		{
			auto DetectedTransformActor = Cast<AFPGTransformActor>(DetectedActor);
			return DetectedTransformActor;
		}
	}

	return nullptr;
}

void AFPGCharacter::OnStartHold()
{
	if (!CurrentDetectActor) return;

	const auto DetectedActorLocation = CurrentDetectActor->GetActorLocation();
	const auto ActorLocation = GetActorLocation();

	Distance = (DetectedActorLocation - ActorLocation).Length();
	UE_LOG(FPGCharacter, Warning, TEXT("Distance:%f"), Distance);
	const FVector InitDirection = (DetectedActorLocation - ActorLocation).GetSafeNormal();
	
	bHolding = true;
}

void AFPGCharacter::OnStopHold()
{
	if (!CurrentDetectActor) return;
	FVector ViewLocation;
	FRotator ViewRotation;
	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	CurrentDetectActor->StartTest(
		this,
		CurrentDetectActor->GetActorLocation(),
		CurrentDetectActor->GetActorScale(),
		GetActorForwardVector(),
		Distance);
	CurrentDetectActor->SetCanShowHighlight(false);
	bHolding = false;
}

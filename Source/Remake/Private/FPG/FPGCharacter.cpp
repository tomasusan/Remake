// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/FPGCharacter.h"

#include "BackpackComponent.h"
#include "BaseInteractableActor.h"
#include "FPGTransformActor.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "FPGHUD.h"
#include "FPGGameInstance.h"
#include "PickableActor.h"

DEFINE_LOG_CATEGORY_STATIC(FPGCharacterLog, All, All);

// Sets default values
AFPGCharacter::AFPGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>("BackpackComponent");
}

// Called when the game starts or when spawned
void AFPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitCameraTransform = CameraComponent->GetRelativeTransform();


	//OnShowDetectedItemInfo.AddUObject();
}

// Called every frame
void AFPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDetectInteractiveActor)
	{
		HandleDetectInteractableActor();
	}
	else
	{
		if (bDetectTransformActor)
		{
			HandleDetectTransformActor();
		}
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
		PlayerInputComponent->BindAction("SwitchWidget", IE_Pressed, this, &AFPGCharacter::SwitchWidget);
		PlayerInputComponent->BindAction("Pick", IE_Pressed, this, &AFPGCharacter::Pick);
		PlayerInputComponent->BindAction("OpenShop", IE_Pressed, this, &AFPGCharacter::OpenShopWidget);


		//Followings are deprecated input settings
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPGCharacter::OnStartHoldTransform);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPGCharacter::OnStopHoldTransform);
	}
}

TArray<FBasicInteractableItemInfo> AFPGCharacter::GetItems() const
{
	return BackpackComponent->GetBackpack();
}

TArray<FBasicInteractableItemInfo> AFPGCharacter::GetItemsByType(const EItemType Type) const
{
	TArray<FBasicInteractableItemInfo> TypeItems;
	for(auto Item:GetItems())
	{
		if(Item.Type == Type)
		{
			TypeItems.Add(Item);
		}
	}
	return TypeItems;
}

FBasicInteractableItemInfo AFPGCharacter::ReportDetectedItemInfo()
{
	FBasicInteractableItemInfo RetVal;
	if (CurrentDetectInteractableActor)
	{
		RetVal = CurrentDetectInteractableActor->GetBasicInfo();
	}
	return RetVal;
}

void AFPGCharacter::MoveForward(const float Val)
{
	AddMovementInput(GetActorForwardVector(), Val);
	if (!FMath::IsNearlyZero(Val))
	{
		CameraShake();
	}
}

void AFPGCharacter::MoveRight(const float Val)
{
	AddMovementInput(GetActorRightVector(), Val);
}

void AFPGCharacter::LookUp(float Val)
{
	if (!bEnableLookAround) return;
	AddControllerPitchInput(Val);
}

void AFPGCharacter::LookRight(float Val)
{
	if (!bEnableLookAround) return;
	AddControllerYawInput(Val);
}

void AFPGCharacter::Pick()
{
	if (!CurrentDetectInteractableActor) return;
	if (CurrentDetectInteractableActor && CurrentDetectInteractableActor->GetBasicInfo().bPickable && CurrentDetectInteractableActor->IsA<APickableActor>())
	{
		UE_LOG(FPGCharacterLog, Display, TEXT("In Picking"));
		BackpackComponent->PickItem(CurrentDetectInteractableActor->GetBasicInfo());
		CurrentDetectInteractableActor->Destroy();
		CurrentDetectInteractableActor = nullptr;
		OnHideDetectedItemInfo.Broadcast();
	}
}

void AFPGCharacter::OpenShopWidget()
{
	if(!CurrentDetectInteractableActor) return;
	if(CurrentDetectInteractableActor->IsA<ABaseShop>())
	{
		UE_LOG(FPGCharacterLog, Warning, TEXT("Open Shop"));
		GetGameInstance<UFPGGameInstance>()->SetCurrentActiveShop(Cast<ABaseShop>(CurrentDetectInteractableActor));
		OnOpenShop.Broadcast();
	}
	else
	{
		UE_LOG(FPGCharacterLog, Warning, TEXT("No Shop Found!"));
	}
	
}

ABaseInteractableActor* AFPGCharacter::DetectInteractableActor() const
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
		if (DetectedActor->IsA<ABaseInteractableActor>())
		{
			auto DetectedInteractableActor = Cast<ABaseInteractableActor>(DetectedActor);
			if (DetectedInteractableActor->GetBasicInfo().bDetectable)
			{
				return DetectedInteractableActor;
			}
			else
			{
				return nullptr;
			}
		}
	}

	return nullptr;
}

void AFPGCharacter::HandleDetectInteractableActor()
{
	if (bDetectInteractiveActor)
	{
		const auto DetectedActor = DetectInteractableActor();
		if (DetectedActor)
		{
			if (!LastDetectInteractableActor)
			{
				LastDetectInteractableActor = CurrentDetectInteractableActor;
				CurrentDetectInteractableActor = DetectedActor;
				const auto DetectedActorInfo = DetectedActor->GetBasicInfo();
				//UE_LOG(FPGCharacterLog, Warning, TEXT("ItemName: %s, ItemDescription: %s"),*DetectedActorInfo.ItemName.ToString(), *DetectedActorInfo.ItemDescription.ToString());
				if(CurrentDetectInteractableActor->GetBasicInfo().bShowHint)
				{
					OnShowDetectedItemInfo.Broadcast();
				}
				CurrentDetectInteractableActor->Detected();
			}
			else if (LastDetectInteractableActor != DetectedActor)
			{
				LastDetectInteractableActor->LoseDetected();
				LastDetectInteractableActor = CurrentDetectInteractableActor;
				CurrentDetectInteractableActor = DetectedActor;
				CurrentDetectInteractableActor->Detected();
				if(CurrentDetectInteractableActor->GetBasicInfo().bShowHint)
				{
					OnUpdateHintInfo.Broadcast();
				}
			}
		}
		else
		{
			LastDetectInteractableActor = CurrentDetectInteractableActor;
			CurrentDetectInteractableActor = nullptr;
			if (LastDetectInteractableActor)
			{
				if(LastDetectInteractableActor->GetBasicInfo().bShowHint)
				{
					OnHideDetectedItemInfo.Broadcast();
				}
				LastDetectInteractableActor->LoseDetected();
			}
		}
	}
}

//The following function has been deprecated, but this doesn't necessarily mean following functions don't work

//This function is to detect TransformActors and return a pointer referring to an instance. Returns nullptr if none instance is detected
AFPGTransformActor* AFPGCharacter::DetectTransformActor() const
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
			UE_LOG(FPGCharacterLog, Warning, TEXT("Detected!"));
			auto DetectedTransformActor = Cast<AFPGTransformActor>(DetectedActor);
			return DetectedTransformActor;
		}
	}

	return nullptr;
}

//Deprecated function
//This function is to handle TransformActor's StartHold event
void AFPGCharacter::OnStartHoldTransform()
{
	if (!bDetectTransformActor) return;
	if (!CurrentDetectTransformActor) return;

	const auto DetectedActorLocation = CurrentDetectTransformActor->GetActorLocation();
	const auto ActorLocation = GetActorLocation();

	Distance = (DetectedActorLocation - ActorLocation).Length();
	UE_LOG(FPGCharacterLog, Warning, TEXT("Distance:%f"), Distance);
	const FVector InitDirection = (DetectedActorLocation - ActorLocation).GetSafeNormal();

	bHolding = true;
}

//Deprecated function
//This function is to handle TransformActor's StopHold event.
void AFPGCharacter::OnStopHoldTransform()
{
	if (!bDetectTransformActor) return;
	if (!CurrentDetectTransformActor) return;
	FVector ViewLocation;
	FRotator ViewRotation;
	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	CurrentDetectTransformActor->StartTest(
		this,
		CurrentDetectTransformActor->GetActorLocation(),
		CurrentDetectTransformActor->GetActorScale(),
		GetActorForwardVector(),
		Distance);
	CurrentDetectTransformActor->SetCanShowHighlight(false);
	bHolding = false;
}

//Deprecated function
//This function is to handle detecting TransformActor by ticking
//To enable this function, you need to enable DetectTransform in category "Detect" in blueprint derived from this class. However this may cause some unexpected errors
void AFPGCharacter::HandleDetectTransformActor()
{
	if (bDetectTransformActor)
	{
		auto DetectedActor = DetectTransformActor();
		if (DetectedActor)
		{
			CurrentDetectTransformActor = DetectedActor;
			if (DetectedActor != LastDetectTransformActor)
			{
				if (LastDetectTransformActor)
					LastDetectTransformActor->HideHighlight();
				LastDetectTransformActor = DetectedActor;
				DetectedActor->OnDetected();
			}
			if (bHolding && CurrentDetectTransformActor)
			{
				FVector ViewLocation;
				FRotator ViewRotation;
				GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

				const auto DetectedActorDirection = ViewRotation.Vector();
				DesiredTransform = CurrentDetectTransformActor->GetActorTransform();
				LastTransform = CurrentDetectTransformActor->GetActorTransform();

				const FVector NewDetectedActorLocation = ViewLocation + DetectedActorDirection * Distance;
				DesiredTransform.SetLocation(NewDetectedActorLocation);
				CurrentDetectTransformActor->UpdateLocation(DesiredTransform);

				if (CurrentDetectTransformActor->IsInCollision())
					CurrentDetectTransformActor->UpdateLocation(LastTransform);
			}
		}
		else
		{
			if (LastDetectTransformActor)
			{
				LastDetectTransformActor->HideHighlight();
				LastDetectTransformActor = nullptr;
			}
			CurrentDetectTransformActor = nullptr;
			bHolding = false;
		}
	}
}

void AFPGCharacter::SwitchWidget()
{
	const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
	const auto GameHUD = Cast<AFPGHUD>(GameInstance->GetCurrentHUD());
	//bEnableLookAround = !bEnableLookAround;
	GameHUD->SwitchWidget();
}

//Deprecated function
//This function hasn't been implemented yet
void AFPGCharacter::StartCameraShake()
{
}

//Deprecated function
//This function hasn't been implemented yet
void AFPGCharacter::CameraShake()
{
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor/BaseInteractableActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABaseInteractableActor::ABaseInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	InteractableActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("InteractableActorMesh");
	InteractableActorMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	InitActorInfo();
	
}

// Called every frame
void ABaseInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInteractableActor::Detected()
{
	
}

void ABaseInteractableActor::LoseDetected()
{
}

void ABaseInteractableActor::InitActorInfo()
{
	const auto RowInfo = BasicDataTable->FindRow<FBasicInteractableItemInfo>(ItemName, "GetBasicInfo", true);
	checkf(RowInfo, TEXT("Find No Rowinfo"));
	BasicInfo = *RowInfo;
}

/*LoginId:f424aaed4470e0d533bf1782766170a2
EpicAccountId:d826da8c6fba4fda9b0d0b583419a15a

Assertion failed: OwningCharacter [File:E:\UEPJ\Remake\Source\Remake\Private\Shop\ShopComponent.cpp] [Line: 19] Owning Character Cast Fail

UnrealEditor_Remake!UShopComponent::BeginPlay() [E:\UEPJ\Remake\Source\Remake\Private\Shop\ShopComponent.cpp:19]
UnrealEditor_Engine
UnrealEditor_Remake!ABaseInteractableActor::BeginPlay() [E:\UEPJ\Remake\Source\Remake\Private\InteractiveActor\BaseInteractableActor.cpp:27]
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor
UnrealEditor
UnrealEditor
UnrealEditor
UnrealEditor
UnrealEditor
kernel32
ntdll*/
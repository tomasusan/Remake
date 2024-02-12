// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor/BaseInteractableActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

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


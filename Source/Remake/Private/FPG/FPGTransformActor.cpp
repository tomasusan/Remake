// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/FPGTransformActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(TransformActorLog, All, All);

// Sets default values
AFPGTransformActor::AFPGTransformActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	HighlightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("HighlightComponent");
	HighlightMeshComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AFPGTransformActor::BeginPlay()
{
	Super::BeginPlay();
	HighlightMeshComponent->SetStaticMesh(StaticMeshComponent->GetStaticMesh());
	HighlightMeshComponent->SetRelativeTransform(StaticMeshComponent->GetRelativeTransform());
	
	for (int32 i = 0; i < HighlightMeshComponent->GetMaterials().Num(); i++)
	{
		HighlightMeshComponent->SetMaterial(i, HighlightMaterial);
	}
	HighlightMeshComponent->SetVisibility(false);
	//ShowHighlight();
}

// Called every frame
void AFPGTransformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPGTransformActor::OnDetected()
{
	UE_LOG(TransformActorLog, Error, TEXT("On Detected!"));
	ShowHighlight();
}

void AFPGTransformActor::ShowHighlight()
{
	//if(HighlightMeshComponent->IsVisible()) return;
	if(!HighlightMaterial) return;
	HighlightMeshComponent->SetVisibility(true);
}

void AFPGTransformActor::HideHighlight()
{
	if(!HighlightMeshComponent) return;
	HighlightMeshComponent->SetVisibility(false);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/FPGTransformActor.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
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

	TestingSphere = CreateDefaultSubobject<USphereComponent>("Testing Sphere");
	TestingSphere->SetupAttachment(GetRootComponent());

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisionSphere->SetupAttachment(GetRootComponent());
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
}

// Called every frame
void AFPGTransformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPGTransformActor::OnDetected()
{
	//UE_LOG(TransformActorLog, Error, TEXT("On Detected!"));
	if (!CanShowHighlight) return;
	ShowHighlight();
}

void AFPGTransformActor::ShowHighlight()
{
	//if(HighlightMeshComponent->IsVisible()) return;
	if (!HighlightMaterial) return;
	HighlightMeshComponent->SetVisibility(true);
}

void AFPGTransformActor::HideHighlight()
{
	if (!HighlightMeshComponent) return;
	HighlightMeshComponent->SetVisibility(false);
}

void AFPGTransformActor::UpdateLocation(FTransform NewTransform)
{
	SetActorTransform(NewTransform);
}

bool AFPGTransformActor::IsInCollision() const
{
	return !CanTransform;
}

void AFPGTransformActor::StartTest(AActor* OwningActor, FVector InitLocation, FVector InitScale, FVector InitDirection,
                                   float InitDistance)
{
	TestSphereRateStaticMesh = TestingSphere->GetComponentScale().X / StaticMeshComponent->GetComponentScale().X;
	TestSphereRateCollision = TestingSphere->GetComponentScale().X / CollisionSphere->GetComponentScale().X;
	TestSphereRateHighlight = TestingSphere->GetComponentScale().X / HighlightMeshComponent->GetComponentScale().X;
	TestDirection = InitDirection;
	OwningActorLocation = OwningActor->GetActorLocation();
	TestLocation = InitLocation + InitDirection * BasicDistance;
	TransformScaleRate = TestingSphere->GetComponentScale() / InitDistance;
	//BeginScale = InitScale;
	TestDistance = InitDistance;
	TestingSphere->SetCollisionObjectType(ECC_WorldDynamic);
	GetWorld()->GetTimerManager().SetTimer(TestTimerHandle, this, &AFPGTransformActor::OnTest, Frequency, true);
}

void AFPGTransformActor::StopTest()
{
	if ((GetWorld()->GetTimerManager().TimerExists(TestTimerHandle)))
	{
		UE_LOG(TransformActorLog, Error, TEXT("Now Stop Testing"));
		TestingSphere->SetCollisionObjectType(ECC_Pawn);
		GetWorld()->GetTimerManager().ClearTimer(TestTimerHandle);
		SetActorLocation(TestingSphere->GetComponentLocation());
		TestingSphere->SetWorldLocation(GetActorLocation());
		StaticMeshComponent->SetWorldScale3D(TestingSphere->GetComponentScale() / TestSphereRateStaticMesh);
		CollisionSphere->SetWorldScale3D(TestingSphere->GetComponentScale() / TestSphereRateCollision);
		HighlightMeshComponent->SetWorldScale3D(TestingSphere->GetComponentScale() / TestSphereRateHighlight);
		//CanShowHighlight = false;
		SetSimulation();
	}
}

void AFPGTransformActor::OnTest()
{
	UE_LOG(TransformActorLog, Warning, TEXT("Now Testing"));
	const FVector PreTestSphereLocation = TestingSphere->GetComponentLocation();
	const FVector PreTestSphereScale = TestingSphere->GetComponentScale();
	//SetActorLocation(TestLocation + TestDirection * TestStep);
	//SetActorScale3D(TestDistance * TransformScaleRate);
	TestingSphere->SetWorldLocation(TestLocation + TestDirection * TestStep);
	TestingSphere->SetWorldScale3D(TestDistance * TransformScaleRate);
	if (GetTestSphereState())
	{
		UE_LOG(TransformActorLog, Error, TEXT("Find Collision"));
		TestingSphere->SetWorldLocation(PreTestSphereLocation);
		TestingSphere->SetWorldScale3D(PreTestSphereScale);
		StopTest();
	}
	TestLocation = TestLocation + TestDirection * TestStep;
	TestDistance = (TestLocation - OwningActorLocation).Length();
}

void AFPGTransformActor::OnBeginOverlap(AActor* OtherActor)
{
	//if()
	UE_LOG(TransformActorLog, Warning, TEXT("Begin Overlap"));
	CanTransform = false;
}

void AFPGTransformActor::OnEndOverlap()
{
	UE_LOG(TransformActorLog, Warning, TEXT("End Overlap"));
	CanTransform = true;
}

void AFPGTransformActor::AssembleAllComponent()
{
	const auto StaticMeshLocation = StaticMeshComponent->GetComponentLocation();
	SetActorLocation(StaticMeshLocation);
	HighlightMeshComponent->SetWorldLocation(StaticMeshLocation);
	CollisionSphere->SetWorldLocation(StaticMeshLocation);
	TestingSphere->SetWorldLocation(StaticMeshLocation);
	SetCanShowHighlight(true);
}

void AFPGTransformActor::SetCanShowHighlight(const bool bCanShowHighlight)
{
	CanShowHighlight = bCanShowHighlight;
	HighlightMeshComponent->SetVisibility(false);
}

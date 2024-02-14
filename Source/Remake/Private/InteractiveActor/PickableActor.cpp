// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor/PickableActor.h"

APickableActor::APickableActor()
{
}

void APickableActor::Detected()
{
	Super::Detected();
	//DetectedWidget->SetVisibility(true);
	PlayAnimationFadeIn();
}

void APickableActor::LoseDetected()
{
	Super::LoseDetected();
	//DetectedWidget->SetVisibility(false);
	PlayAnimationFadeout();
}

void APickableActor::BeginPlay()
{
	Super::BeginPlay();
	//DetectedWidget->SetVisibility(false);
}

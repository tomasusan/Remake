// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DetectedWidget.h"
#include "BaseInteractableActor.h"

void UDetectedWidget::SetOwner(ABaseInteractableActor* Owner)
{
	OwningInteractableActor = Owner;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetectedWidget.generated.h"

class ABaseInteractableActor;
/**
 * 
 */
UCLASS()
class REMAKE_API UDetectedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetOwner(ABaseInteractableActor* Owner);

	UFUNCTION(BlueprintCallable)
	ABaseInteractableActor* GetInteractableActorOwner() const { return OwningInteractableActor; };

private:
	UPROPERTY()
	ABaseInteractableActor* OwningInteractableActor = nullptr;
};

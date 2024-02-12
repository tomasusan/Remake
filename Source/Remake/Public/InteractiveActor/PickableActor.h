// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor/BaseInteractableActor.h"
#include "PickableActor.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class REMAKE_API APickableActor : public ABaseInteractableActor
{
	GENERATED_BODY()

public:
	APickableActor();
	
	virtual void Detected() override;
	virtual void LoseDetected() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnimationFadeIn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnimationFadeout();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UWidgetComponent* DetectedWidget;
};

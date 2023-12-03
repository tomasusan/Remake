// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RemakeAIController.generated.h"

class URemakeAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class REMAKE_API ARemakeAIController : public AAIController
{
	GENERATED_BODY()

	ARemakeAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AIComponent")
	URemakeAIPerceptionComponent* AIPerceptionComponent;
	
};

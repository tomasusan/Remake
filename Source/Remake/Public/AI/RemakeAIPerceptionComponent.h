// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "RemakeAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API URemakeAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClosestActor() const;
};

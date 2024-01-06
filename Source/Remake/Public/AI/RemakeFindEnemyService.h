// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RemakeFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API URemakeFindEnemyService : public UBTService
{
	GENERATED_BODY()
	URemakeFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
};

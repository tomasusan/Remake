// Fill out your copyright notice in the Description page of Project Settings.


#include "RemakeAIController.h"
#include "AICharacter.h"
#include "RemakeAIPerceptionComponent.h"

ARemakeAIController::ARemakeAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<URemakeAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ARemakeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AAICharacter>(InPawn);
	if(AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}

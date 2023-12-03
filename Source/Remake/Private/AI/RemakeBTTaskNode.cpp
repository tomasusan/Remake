// Fill out your copyright notice in the Description page of Project Settings.


#include "RemakeBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RemakeAIController.h"
#include "NavigationSystem.h"

URemakeBTTaskNode::URemakeBTTaskNode()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type URemakeBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !BlackBoard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSys) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	const auto Found = NavSys->GetRandomReachablePointInRadius(Pawn->GetVelocity(), Radius, NavLocation);

	if(!Found) return EBTNodeResult::Failed;

	BlackBoard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BaseCharacterMovementComponent.h"
#include "BaseCharacter.h"

float UBaseCharacterMovementComponent::GetMaxSpeed() const
{
	const auto MaxSpeed = Super::GetMaxSpeed();
	const auto Player = Cast<ABaseCharacter>(GetOwner());
	return Player && Player->IsSprinting() ? MaxSpeed * SprintModifier: MaxSpeed;
}

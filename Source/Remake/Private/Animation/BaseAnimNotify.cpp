// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BaseAnimNotify.h"

#include "BaseCharacter.h"

void UBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UAnimNotify::Notify(MeshComp, Animation, EventReference);
	OnNotified.Broadcast();
}

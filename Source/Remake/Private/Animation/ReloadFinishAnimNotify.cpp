// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ReloadFinishAnimNotify.h"

void UReloadFinishAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimNotify.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ReloadFinishAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class REMAKE_API UReloadFinishAnimNotify : public UBaseAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

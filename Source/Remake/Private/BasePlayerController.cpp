// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "Framework/Application/NavigationConfig.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController()) {
		auto navigation = MakeShared<FNavigationConfig>();
		navigation->bTabNavigation = false;
		FSlateApplication::Get().SetNavigationConfig(navigation);
	}
}

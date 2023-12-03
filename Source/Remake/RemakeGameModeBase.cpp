// Copyright Epic Games, Inc. All Rights Reserved.


#include "RemakeGameModeBase.h"
#include "BaseCharacter.h"
#include "BasePlayerController.h"

ARemakeGameModeBase::ARemakeGameModeBase()
{
	DefaultPawnClass=ABaseCharacter::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();
}

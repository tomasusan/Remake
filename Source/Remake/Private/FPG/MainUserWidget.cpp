// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/MainUserWidget.h"
#include "FPGCharacter.h"

FBasicInteractableItemInfo UMainUserWidget::GetDetectedItemInfo()
{
	const auto PlayerCharacterController = GetOwningPlayer();
	const auto PlayerCharacter = Cast<AFPGCharacter>(PlayerCharacterController->GetPawn());
	checkf(PlayerCharacter, TEXT("MainUserWidget casting owning player to AFPGCharacter failed"));

	return PlayerCharacter->ReportDetectedItemInfo();
}
/*
LoginId:f424aaed4470e0d533bf1782766170a2
EpicAccountId:d826da8c6fba4fda9b0d0b583419a15a

Assertion failed: PlayerCharacter [File:E:\UEPJ\Remake\Source\Remake\Private\FPG\MainUserWidget.cpp] [Line: 11] MainUserWidget casting owning player to AFPGCharacter failed

UnrealEditor_Remake!UMainUserWidget::GetDetectedItemInfo() [E:\UEPJ\Remake\Source\Remake\Private\FPG\MainUserWidget.cpp:11]
UnrealEditor_Remake!UMainUserWidget::execGetDetectedItemInfo() [E:\UEPJ\Remake\Intermediate\Build\Win64\UnrealEditor\Inc\Remake\UHT\MainUserWidget.gen.cpp:23]
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_Remake!TBaseUObjectMethodDelegateInstance<1,AFPGHUD const ,void __cdecl(void),FDefaultDelegateUserPolicy>::ExecuteIfSafe() [F:\UnrealEngine5_2_1\UE_5.2\Engine\Source\Runtime\Core\Public\Delegates\DelegateInstancesImpl.h:552]
UnrealEditor_Remake!TMulticastDelegateBase<FDefaultDelegateUserPolicy>::Broadcast<IBaseDelegateInstance<void __cdecl(void),FDefaultDelegateUserPolicy>,TDelegate<void __cdecl(void),FDefaultDelegateUserPolicy> >() [F:\UnrealEngine5_2_1\UE_5.2\Engine\Source\Runtime\Core\Public\Delegates\MulticastDelegateBase.h:204]
UnrealEditor_Remake!AFPGCharacter::HandleDetectInteractableActor() [E:\UEPJ\Remake\Source\Remake\Private\FPG\FPGCharacter.cpp:145]
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Core
UnrealEditor_Core
UnrealEditor_Core
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_Engine
UnrealEditor_UnrealEd
UnrealEditor_UnrealEd
UnrealEditor
UnrealEditor
UnrealEditor
UnrealEditor
UnrealEditor
UnrealEditor
kernel32
ntdll
*/
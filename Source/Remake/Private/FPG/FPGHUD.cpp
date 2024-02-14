// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/FPGHUD.h"
#include "MainUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "FPGGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(FPGHUDLog, All, All);

void AFPGHUD::BeginPlay()
{
	Super::BeginPlay();
	MainUserWidget = CreateWidget<UMainUserWidget>(GetWorld(), MainUserWidgetClass, "MainUserWidget");
	checkf(MainUserWidget, TEXT("MainUserWidget Create Failed"));
	MainUserWidget->AddToViewport();

	Character = Cast<AFPGCharacter>(GetOwningPawn());
	Character->OnShowDetectedItemInfo.AddUObject(this, &AFPGHUD::OnShowItemHint);
	Character->OnHideDetectedItemInfo.AddUObject(this, &AFPGHUD::OnHideItemHint);
	Character->OnUpdateHintInfo.AddUObject(this, &AFPGHUD::UpdateHintInfo);
	Character->OnOpenShop.AddUObject(this, &AFPGHUD::OpenShopWidget);

	const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
	GameInstance->SetCurrentHUD(this);
}

void AFPGHUD::SwitchWidget()
{
	MainUserWidget->SwitchWidget();
}

void AFPGHUD::OpenShopWidget()
{
	UE_LOG(FPGHUDLog, Warning, TEXT("Calling Delegate Suceess"));
	MainUserWidget->OpenShopWidget();
}

void AFPGHUD::OnShowItemHint() const
{
	MainUserWidget->ShowHint();
}

void AFPGHUD::OnHideItemHint() const
{
	MainUserWidget->HideHint();
}

void AFPGHUD::UpdateHintInfo()
{
	MainUserWidget->UpdateHintInfo();
}

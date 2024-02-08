// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG/FPGHUD.h"
#include "MainUserWidget.h"
#include "Blueprint/UserWidget.h"

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
}

void AFPGHUD::OnShowItemHint() const
{
	MainUserWidget->ShowHint();
}

void AFPGHUD::OnHideItemHint() const
{
	MainUserWidget->HideHint();
}

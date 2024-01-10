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
}

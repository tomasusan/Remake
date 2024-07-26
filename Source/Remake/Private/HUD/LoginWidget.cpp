// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LoginWidget.h"
#include "UserHelper.h"

void ULoginWidget::WidgetInit()
{
	Helper = new UserHelper;
}

void ULoginWidget::LoadInfo(const FString& Username, const FString& Psw)
{
	Helper->GetUserInfo(Username, Psw);
}

bool ULoginWidget::IsInfoValid(int32& Score)
{
	return Helper->IsValid(Score);
}

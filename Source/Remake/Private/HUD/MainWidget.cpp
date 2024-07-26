// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainWidget.h"

void UMainWidget::InitTime(int32 m, int32 s, int32 ms)
{
	Time = UTime::CreateTime(m, s, ms);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWindowWidget.h"

void UUIWindowWidget::OnWindowClose()
{
}

void UUIWindowWidget::OnWindowOpen()
{
}

void UUIWindowWidget::ChangeActiveState(bool NewState)
{
	if(IsActive == NewState)return;
	IsActive = NewState;
	OnWindowActiveStateChanged.Broadcast();
	SetVisibility(IsActive?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
}

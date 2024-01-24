// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWindowWidget.h"

void UUIWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
}

void UUIWindowWidget::OnWindowClose()
{
}

void UUIWindowWidget::OnWindowOpen()
{
	SetFocus();
}

void UUIWindowWidget::ChangeActiveState(bool NewState)
{
	if(IsActive == NewState)return;
	IsActive = NewState;
	OnActiveStateChanged.Broadcast();
	SetVisibility(IsActive?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
}

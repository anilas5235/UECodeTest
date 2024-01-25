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

void UUIWindowWidget::ChangeActiveState(const bool NewState, const bool bIgnoreActive)
{	
	if(IsActive == NewState && !bIgnoreActive)return;
	IsActive = NewState;
	SetVisibility(IsActive ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);	
	if(OnActiveStateChanged.IsBound()) OnActiveStateChanged.Broadcast();
}

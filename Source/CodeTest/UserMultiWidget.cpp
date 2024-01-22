// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMultiWidget.h"

void UUserMultiWidget::NativeConstruct()
{
	Super::NativeConstruct();	
	
	if(WidgetClasses.IsEmpty()){ UE_LOG(LogTemp,Warning,TEXT("MultiWiget: there are no Widget Classes selected!"));return;}	

	for (const auto WidgetClass : WidgetClasses)
	{
		const auto NewWidget =CreateWidget(this,WidgetClass);
		CreatedWidgets.Add(NewWidget);
		MyWidgetSwitcher->AddChild(NewWidget);
	}

	if(CurrentlyActiveIndex <0 || CurrentlyActiveIndex >= CreatedWidgets.Num()){SwitchWidget(0);}
	else{SwitchWidget(CurrentlyActiveIndex);}
	
}

void UUserMultiWidget::SwitchWidget(const int Index)
{
	if(Index <0 || Index >= CreatedWidgets.Num() || Index == CurrentlyActiveIndex)return;

	if(Index == 0)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	if(CurrentlyActiveIndex ==0)
	{
		SetVisibility(ESlateVisibility::Visible);
	}

	CurrentlyActiveIndex = Index;
	CurrentlyActiveWidget = CreatedWidgets[Index];

	MyWidgetSwitcher->SetActiveWidgetIndex(CurrentlyActiveIndex);
}

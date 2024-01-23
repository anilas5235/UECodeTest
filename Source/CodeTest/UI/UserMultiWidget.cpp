// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMultiWidget.h"

void UUserMultiWidget::NativeConstruct()
{
	Super::NativeConstruct();	
	
	if(WidgetClasses.IsEmpty()){ UE_LOG(LogTemp,Warning,TEXT("MultiWiget: there are no Widget Classes selected!"));return;}	

	for (const auto WidgetClass : WidgetClasses)
	{
		const auto NewWidget =CreateWidget(this,WidgetClass);
		CreatedWidgets.Add(Cast<UUIWindowWidget>(NewWidget));
		MyWidgetSwitcher->AddChild(NewWidget);
	}

	if(CurrentlyActiveIndex <-1 || CurrentlyActiveIndex >= CreatedWidgets.Num()){StartIndex =-1;}
	else{SwitchWidget(StartIndex);}	
}

void UUserMultiWidget::SwitchWidget(const int Index)
{	
	if(Index <-1 || Index >= CreatedWidgets.Num() || Index == CurrentlyActiveIndex)return;

	if(CurrentlyActiveWidget) CurrentlyActiveWidget->OnWindowClose();	

	if(Index == -1)	{ChangeActiveState(false);}	
	if(CurrentlyActiveIndex ==-1){ChangeActiveState(true);}	

	CurrentlyActiveIndex = Index;

	if(CurrentlyActiveIndex >=0)
	{
		CurrentlyActiveWidget = CreatedWidgets[CurrentlyActiveIndex];
		CurrentlyActiveWidget->OnWindowOpen();
		MyWidgetSwitcher->SetActiveWidgetIndex(CurrentlyActiveIndex);
	}
	else
	{
		CurrentlyActiveWidget = nullptr;
	}	
}

void UUserMultiWidget::SwitchToEmpty()
{
	SwitchWidget(-1);
}

void UUserMultiWidget::OnWindowOpen()
{
	Super::OnWindowOpen();
}

void UUserMultiWidget::OnWindowClose()
{
	Super::OnWindowClose();
}


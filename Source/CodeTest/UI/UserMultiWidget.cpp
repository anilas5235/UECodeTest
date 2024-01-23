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

	if(CurrentlyActiveIndex <-1 || CurrentlyActiveIndex >= CreatedWidgets.Num()){StartIndex =-1;}
	else{SwitchWidget(StartIndex);}	
}

void UUserMultiWidget::OnWindowOpen_Implementation()
{
	IUIWindow::OnWindowOpen_Implementation();
}

void UUserMultiWidget::OnWindowClose_Implementation()
{
	IUIWindow::OnWindowClose_Implementation();
}

void UUserMultiWidget::ChangeActiveState(const bool NewState)
{
	if(IsActive == NewState)return;
	IsActive = NewState;
	SetVisibility(IsActive?ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	OnWindowActiveStateChanged.Broadcast();
}

void UUserMultiWidget::SwitchWidget(const int Index)
{	
	if(Index <-1 || Index >= CreatedWidgets.Num() || Index == CurrentlyActiveIndex)return;

	if(const auto Inter = Cast<IUIWindow>(CurrentlyActiveWidget)){Inter->OnWindowClose();}		

	if(Index == -1)
	{		
		ChangeActiveState(false);
		return;
	}

	if(CurrentlyActiveIndex ==-1){ChangeActiveState(true);}

	CurrentlyActiveIndex = Index;
	CurrentlyActiveWidget = CreatedWidgets[Index];

	MyWidgetSwitcher->SetActiveWidgetIndex(CurrentlyActiveIndex);

	if(const auto Inter = Cast<IUIWindow>(CurrentlyActiveWidget)){Inter->OnWindowOpen();}		
}

void UUserMultiWidget::SwitchToEmpty()
{
	SwitchWidget(-1);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUDBase.h"

void ACustomHUDBase::BeginPlay()
{
	Super::BeginPlay();
	SetupWidgets();
}

void ACustomHUDBase::UpdateUIState()
{
	if(!MainMultiWidgetRunTimeInstance) return;
	const bool NewState =MainMultiWidgetRunTimeInstance->IsActive;
	if(NewState == IsMainUIActive) return;
	IsMainUIActive = NewState;

	const auto MyPlayerController = GetOwningPlayerController();
	MyPlayerController->SetShowMouseCursor(IsMainUIActive);	

	if(IsMainUIActive)
	{
		MyPlayerController->SetInputMode(FInputModeUIOnly());
	}
	else
	{
		MyPlayerController->SetInputMode(FInputModeGameOnly());
	}	
	
}

void ACustomHUDBase::SwitchMainWidget(const int Index)
{
	if(!MainMultiWidgetRunTimeInstance) return;
	MainMultiWidgetRunTimeInstance->SwitchWidget(Index);
}

void ACustomHUDBase::SetupWidgets()
{
	if(!MainMultiWidgetClass)
	{UE_LOG(LogTemp,Error,TEXT("%s : There was no MainMultiWidgetClass selected"),*GetNameSafe(this));return;}

	MainMultiWidgetRunTimeInstance = Cast<UUserMultiWidget>(CreateWidget(GetOwningPlayerController(),MainMultiWidgetClass,FName("MainMultiWidget")));
	MainMultiWidgetRunTimeInstance->AddToViewport(1);

	UpdateUIState();
	MainMultiWidgetRunTimeInstance->OnActiveWindowChanged.AddDynamic(this,&ACustomHUDBase::UpdateUIState);
}

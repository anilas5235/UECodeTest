// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUDBase.h"

void ACustomHUDBase::BeginPlay()
{
	Super::BeginPlay();
	SetupWidgets();
}

void ACustomHUDBase::UpdateUIState()
{
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

void ACustomHUDBase::SetupWidgets()
{
	if(!MainMultiWidgetClass)
	{UE_LOG(LogTemp,Error,TEXT("%s : There was no MainMultiWidgetClass selected"),*GetNameSafe(this));return;}

	MainMultiWidgetRunTimeInstance = Cast<UUserMultiWidget>(CreateWidget(GetOwningPlayerController(),MainMultiWidgetClass,FName("MainMultiWidget")));
	MainMultiWidgetRunTimeInstance->AddToViewport(1);

	MainMultiWidgetRunTimeInstance->OnActiveWindowChanged.AddDynamic(this,&ACustomHUDBase::UpdateUIState);
}

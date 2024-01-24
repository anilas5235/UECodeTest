// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoSettingsWindow.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"


void UVideoSettingsWindow::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentGameSettings = UEngine::GetGameUserSettings();
	CurrentGameSettings->LoadSettings();

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(PossibleResolutions);
}

void UVideoSettingsWindow::ChangeResolution(const bool bIncrease)
{
	if(const auto NewIndex = CurrentResolutionIndex+ bIncrease?1:-1; PossibleResolutions.IsValidIndex(NewIndex))
	{
		CurrentResolutionIndex = NewIndex;
		CurrentGameSettings->SetScreenResolution(PossibleResolutions[CurrentResolutionIndex]);
	}
}

void UVideoSettingsWindow::ChangeWindowMode(bool bIncrease)
{
	const EWindowMode::Type Parameter = CurrentGameSettings->GetFullscreenMode();
	const EWindowMode::Type NewParameter =
		static_cast<EWindowMode::Type>(FMath::Clamp(static_cast<uint8>(Parameter) + bIncrease ? 1 : -1, 0, 2));
	if(Parameter == NewParameter) return;	
	CurrentGameSettings->SetFullscreenMode(NewParameter);
}

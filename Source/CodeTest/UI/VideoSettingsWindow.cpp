// Fill out your copyright notice in the Description page of Project Settings.

#include "VideoSettingsWindow.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"


void UVideoSettingsWindow::NativeConstruct()
{
	Super::NativeConstruct();
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(PossibleResolutions);
	LoadSettings();
}

void UVideoSettingsWindow::ChangeResolution(const bool bIncrease)
{
	if(const auto NewIndex = CurrentResolutionIndex+ bIncrease?1:-1; PossibleResolutions.IsValidIndex(NewIndex))
	{
		CurrentResolutionIndex = NewIndex;
		CurrentGameSettings->SetScreenResolution(PossibleResolutions[CurrentResolutionIndex]);
	}
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeWindowMode(bool bIncrease)
{
	const auto Parameter = CurrentGameSettings->GetFullscreenMode();
	const auto NewParameter =
		static_cast<EWindowMode::Type>(FMath::Clamp(static_cast<uint8>(Parameter) + bIncrease ? 1 : -1, 0, sizeof(Parameter)));
	if(Parameter == NewParameter) return;	
	CurrentGameSettings->SetFullscreenMode(NewParameter);
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeVsync(bool bIncrease)
{
	const auto Parameter = CurrentGameSettings->IsVSyncEnabled();
	if(bIncrease == Parameter)return;
	CurrentGameSettings->SetVSyncEnabled(!Parameter);
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeOverAllQualityLevel(bool bIncrease)
{
	const EPerQualityLevels Parameter = static_cast<EPerQualityLevels>(CurrentGameSettings->GetOverallScalabilityLevel());
	const auto NewParameter =
		static_cast<EPerQualityLevels>(FMath::Clamp(static_cast<uint8>(Parameter) + bIncrease ? 1 : -1, 0, sizeof(Parameter)));
	if(Parameter == NewParameter) return;	
	CurrentGameSettings->SetOverallScalabilityLevel(static_cast<int>(NewParameter));
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeFoliageQualityLevel(bool bIncrease)
{
	const EPerQualityLevels Parameter = static_cast<EPerQualityLevels>(CurrentGameSettings->GetFoliageQuality());
	const auto NewParameter =
		static_cast<EPerQualityLevels>(FMath::Clamp(static_cast<uint8>(Parameter) + bIncrease ? 1 : -1, 0, sizeof(Parameter)));
	if(Parameter == NewParameter) return;	
	CurrentGameSettings->SetFoliageQuality(static_cast<int>(NewParameter));
	UpdateUIText();
}

void UVideoSettingsWindow::ApplyAndSave()
{
	CurrentGameSettings->ApplySettings(true);
	CurrentGameSettings->SaveSettings();
	UpdateUIText();
}

void UVideoSettingsWindow::LoadSettings()
{
	CurrentGameSettings = UGameUserSettings::GetGameUserSettings();
	CurrentGameSettings->LoadSettings();
	UpdateUIText();
}

void UVideoSettingsWindow::UpdateUIText_Implementation()
{
}

void UVideoSettingsWindow::OnWindowOpen()
{
	Super::OnWindowOpen();
	LoadSettings();
}

void UVideoSettingsWindow::OnWindowClose()
{
	Super::OnWindowClose();	
}

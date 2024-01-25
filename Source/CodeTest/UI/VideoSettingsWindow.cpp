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
	if(const auto NewIndex = CurrentResolutionIndex + (bIncrease?1:-1); PossibleResolutions.IsValidIndex(NewIndex))
	{
		CurrentResolutionIndex = NewIndex;
		CurrentGameSettings->SetScreenResolution(PossibleResolutions[CurrentResolutionIndex]);
	}	
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeWindowMode(const bool bIncrease)
{
	const auto Parameter = CurrentGameSettings->GetFullscreenMode();  
	const auto NewParameter = EWindowMode::ConvertIntToWindowMode(
		FMath::Clamp(static_cast<int>(Parameter) + (bIncrease ? 1 : -1), 0, 2));	
	if(Parameter == NewParameter) return;
	CurrentGameSettings->SetFullscreenMode(NewParameter);
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeVsync(const bool bIncrease)
{
	const auto Parameter = CurrentGameSettings->IsVSyncEnabled();
	if(bIncrease == Parameter)return;
	CurrentGameSettings->SetVSyncEnabled(!Parameter);
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeOverAllQualityLevel(const bool bIncrease)
{
	const auto OldParameter = CurrentGameSettings->GetOverallScalabilityLevel();
	const auto NewParameter =FMath::Clamp(static_cast<int>(OldParameter) + (bIncrease ? 1 : -1), 0, 4);
	if(OldParameter == NewParameter) return;	
	CurrentGameSettings->SetOverallScalabilityLevel(NewParameter);
	UpdateUIText();
}

void UVideoSettingsWindow::ChangeFoliageQualityLevel(const bool bIncrease)
{
	const auto OldParameter = CurrentGameSettings->GetFoliageQuality();
	const auto NewParameter =FMath::Clamp(static_cast<int>(OldParameter) + (bIncrease ? 1 : -1), 0, 4);
	if(OldParameter == NewParameter) return;
	CurrentGameSettings->SetFoliageQuality(NewParameter);
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
	const auto CurrentRes = CurrentGameSettings->GetScreenResolution();
	for (int i = 0; i < PossibleResolutions.Num(); ++i)
	{
		if(CurrentRes == PossibleResolutions[i]){ CurrentResolutionIndex = i; break;}
	}
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

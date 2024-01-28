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

void UVideoSettingsWindow::ChangeVideoQualityLevel(const EVideoQualityOptions Option, const bool bIncrease)
{
	int NewParameter =0;	
	switch (Option) {
	case EVideoQualityOptions::OverAll:		
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetOverallScalabilityLevel(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetOverallScalabilityLevel(NewParameter);
		}
		break;
	case EVideoQualityOptions::Anti_Aliasing:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetAntiAliasingQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetAntiAliasingQuality(NewParameter);
		}		
		break;
	case EVideoQualityOptions::Post_Processing:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetPostProcessingQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetPostProcessingQuality(NewParameter);
		}
		break;
	case EVideoQualityOptions::Shadows:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetShadowQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetShadowQuality(NewParameter);
		}
		break;
	case EVideoQualityOptions::Global_Illumination:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetGlobalIlluminationQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetGlobalIlluminationQuality(NewParameter);
		}
		break;
	case EVideoQualityOptions::Reflections:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetReflectionQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetReflectionQuality(NewParameter);
		}
		break;
	case EVideoQualityOptions::Textures:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetTextureQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetTextureQuality(NewParameter);
		}
		break;
	case EVideoQualityOptions::Effects:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetVisualEffectQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetVisualEffectQuality(NewParameter);
		}
		break;
	case EVideoQualityOptions::Foliage:		
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetFoliageQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetFoliageQuality(NewParameter);
		}		
		break;
	case EVideoQualityOptions::Shading:
		if(CalculateNewVideoQualityVal(CurrentGameSettings->GetShadingQuality(),bIncrease,NewParameter))
		{
			CurrentGameSettings->SetShadingQuality(NewParameter);
		}
		break;
	default: ;
	}
	UpdateUIText();	
}

bool UVideoSettingsWindow::CalculateNewVideoQualityVal(const int OldVal, const bool bIncrease, int& NewVal)
{
	NewVal = FMath::Clamp(OldVal + (bIncrease ? 1 : -1), 0, 4);
	return OldVal != NewVal;
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

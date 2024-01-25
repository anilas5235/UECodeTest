// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSettingsWindow.h"
#include "Kismet/GameplayStatics.h"



void UAudioSettingsWindow::NativeConstruct()
{
	Super::NativeConstruct();	
	LoadSettings();	
}

void UAudioSettingsWindow::NativePreConstruct()
{
	Super::NativePreConstruct();
	for (auto Name : SliderNames){AudioSliderData.FindOrAdd(Name);}	
}

void UAudioSettingsWindow::OnWindowOpen()
{
	Super::OnWindowOpen();
	LoadSettings();
}

void UAudioSettingsWindow::OnWindowClose()
{
	Super::OnWindowClose();
	SaveSettings();
}

void UAudioSettingsWindow::LoadSettings(const int UserIndex)
{
	if(UGameplayStatics::DoesSaveGameExist(SaveSlotName,UserIndex))
	{
		CurrentSave = Cast<UAudioSave>(UGameplayStatics::LoadGameFromSlot(SaveSlotName,UserIndex));
	}
	else
	{
		CurrentSave = Cast<UAudioSave>( UGameplayStatics:: CreateSaveGameObject(UAudioSave::StaticClass()));
		SaveSettings(UserIndex);
	}
	SetSliderValues();
}

void UAudioSettingsWindow::SaveSettings(const int UserIndex) const
{
	if(!CurrentSave){UE_LOG(LogTemp,Error,TEXT("%s CurrenSave is invaild"),*GetNameSafe(this));}
	UGameplayStatics:: SaveGameToSlot(CurrentSave,SaveSlotName,UserIndex);	
}

void UAudioSettingsWindow::SetAudioSliderVolumePerName(const FName Name, const float Value)
{
	if(!CurrentSave){UE_LOG(LogTemp,Error,TEXT("%s CurrenSave is invaild"),*GetNameSafe(this));}
	if(!(CurrentSave->SliderValues.Contains(Name))){ CurrentSave->SliderValues.Add(Name,Value);}
	else{CurrentSave->SliderValues[Name] = Value;}

	if(AudioSliderData.Contains(Name))
	{
		const auto Data =AudioSliderData[Name];
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),Data.SoundMixer,Data.SoundClass,Value);		
	}	
}

void UAudioSettingsWindow::SetAudioSliderVolumePerIndex(const int Index, const float Value)
{
	if(Index < 0 || Index>= SliderNames.Num())
	{
		UE_LOG(LogTemp,Error,TEXT("%s Index is not vaild"),*GetNameSafe(this));
		return;
	}
	SetAudioSliderVolumePerName(SliderNames[Index],Value);
}

float UAudioSettingsWindow::GetAudioSliderVolumePerName(FName Name)
{
	if(!CurrentSave){UE_LOG(LogTemp,Error,TEXT("%s CurrenSave is invaild"),*GetNameSafe(this)); return -1;}
	if(!CurrentSave->SliderValues.Contains(Name)){ CurrentSave->SliderValues.Add(Name,.8f);}		
	return  CurrentSave->SliderValues[Name];
}

float UAudioSettingsWindow::GetAudioSliderVolumePerIndex(int Index)
{
	if(Index < 0 || Index>= SliderNames.Num())
	{
		UE_LOG(LogTemp,Error,TEXT("%s Index is not vaild"),*GetNameSafe(this));
		return -1;
	}
	return 	GetAudioSliderVolumePerName(SliderNames[Index]);
}

void UAudioSettingsWindow::SetSliderValues_Implementation()
{
}

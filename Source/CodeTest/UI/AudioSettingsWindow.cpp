// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSettingsWindow.h"

#include "Kismet/GameplayStatics.h"


void UAudioSettingsWindow::NativeConstruct()
{
	LoadSettings();	
	Super::NativeConstruct();

	auto MasterKey =FName("Master");
	if(AudioSliderData.Contains(MasterKey))
	{
		const auto Data = AudioSliderData[MasterKey];
		UGameplayStatics::SetBaseSoundMix(GetWorld(),Data.SoundMixer);			
	}

}

void UAudioSettingsWindow::NativePreConstruct()
{
	for (auto Name : StandardSliders)	{AudioSliderData.FindOrAdd(Name);}
	
	Super::NativePreConstruct();
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

void UAudioSettingsWindow::LoadSettings()
{
	if(UGameplayStatics:: DoesSaveGameExist(SaveSlotName,0))
	{
		CurrentSave = Cast<UAudioSave>(UGameplayStatics::LoadGameFromSlot(SaveSlotName,0));
	}
	else
	{
		CurrentSave = Cast<UAudioSave>( UGameplayStatics:: CreateSaveGameObject(UAudioSave::StaticClass()));
		SaveSettings();
	}	
}

void UAudioSettingsWindow::SaveSettings() const
{
	UGameplayStatics:: SaveGameToSlot(CurrentSave,SaveSlotName,0);
}

void UAudioSettingsWindow::SetAudioSliderVolume(FName Name, float Value)
{
	if(!CurrentSave->SliderValues.Contains(Name)){ CurrentSave->SliderValues.Add(Name,Value);}
	else{CurrentSave->SliderValues[Name] = Value;}

	if(AudioSliderData.Contains(Name))
	{
		const auto Data =AudioSliderData[Name];
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),Data.SoundMixer,Data.SoundClass,Value);		
	}
}

float UAudioSettingsWindow::GetAudioSliderVolume(FName Name)
{
	if(!CurrentSave->SliderValues.Contains(Name))return 0;
	return  CurrentSave->SliderValues[Name];
}

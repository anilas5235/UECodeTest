// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSettingsWindow.h"

#include "Kismet/GameplayStatics.h"


void UAudioSettingsWindow::NativeConstruct()
{
	Super::NativeConstruct();

	auto MasterKey =FName("Master");
	if(AudioSliderData.Contains(MasterKey))
	{
		const auto Data = AudioSliderData[MasterKey];
		UGameplayStatics::SetBaseSoundMix(GetWorld(),Data.SoundMixer);			
	}	

	LoadSettings();	
}

void UAudioSettingsWindow::NativePreConstruct()
{
	for (auto Name : StandardSliders)
	{
		AudioSliderData.FindOrAdd(Name);
	}
	
	Super::NativePreConstruct();
}

void UAudioSettingsWindow::OnWindowOpen_Implementation()
{
	IUIWindow::OnWindowOpen_Implementation();
}

void UAudioSettingsWindow::OnWindowClose_Implementation()
{
	IUIWindow::OnWindowClose_Implementation();
	SaveSettings();	
}

void UAudioSettingsWindow::SubToSliderEvents()
{
	for (const auto SliderData : AudioSliderData)
	{
		if(!SliderData.Value.Slider){continue;}
		const auto Slider = Cast<USlider>(SliderData.Value.Slider);
		Slider->OnValueChanged.AddDynamic(this,&UAudioSettingsWindow::UpdateSavedValuesFromSliders);
	}
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

void UAudioSettingsWindow::SetSlidersToSavedValues()
{
	for (const auto SliderData : AudioSliderData)
	{
		const auto Slider = Cast<USlider>(SliderData.Value.Slider);
		auto Key =SliderData.Key;
		if(!Slider) {UE_LOG(LogTemp,Warning,TEXT("Slider for %s not found"),*Key.ToString()) continue;}
		
		if(!CurrentSave->SliderValues.Contains(Key)){ CurrentSave->SliderValues.Add(Key,.8f);}

		Slider->SetValue(CurrentSave->SliderValues[Key]);
		Slider->SetMaxValue(MaxSliderValue);
		Slider->SetMinValue(MinSliderValue);
	}
}

void UAudioSettingsWindow::SetMixersToSavedValues()
{
	for (const auto SliderData : AudioSliderData)
	{		
		if(!SliderData.Value.SoundClass || !SliderData.Value.SoundMixer){continue;}		
		if(!CurrentSave->SliderValues.Contains(SliderData.Key)){ CurrentSave->SliderValues.Add(SliderData.Key,.8f);}		
		
		UGameplayStatics:: SetSoundMixClassOverride(GetWorld(),SliderData.Value.SoundMixer,SliderData.Value.SoundClass,
			CurrentSave->SliderValues[SliderData.Key]);
	}
}

void UAudioSettingsWindow::UpdateSavedValuesFromSliders(float Value)
{
	for (const auto SliderData : AudioSliderData)
	{		
		if(!SliderData.Value.Slider){continue;}

		const float SliderValue = Cast<USlider>(SliderData.Value.Slider)->GetValue();
		if(!CurrentSave->SliderValues.Contains(SliderData.Key)){ CurrentSave->SliderValues.Add(SliderData.Key,SliderValue);}
		else{CurrentSave->SliderValues[SliderData.Key] = SliderValue;}	
	}
}

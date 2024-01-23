// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWindowWidget.h"
#include "CodeTest/MyCustomDataTypes.h"
#include "GameFramework/SaveGame.h"
#include "AudioSettingsWindow.generated.h"

 
UCLASS(BlueprintType)
   class UAudioSave : public USaveGame
{
	GENERATED_BODY()
   
public:
	TMap<FName,float> SliderValues;
};

UCLASS()
class CODETEST_API UAudioSettingsWindow : public UUIWindowWidget
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere,BlueprintReadOnly) TMap<FName,FAudioSliderData> AudioSliderData;	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) UAudioSave* CurrentSave;

protected:
	inline static const FString SaveSlotName = FString("AudioWindowSaveSettings");
	inline static const TArray<FName> StandardSliders = {FName("Master"),FName("Music"),FName("Effects"),FName("Ambience")};
	const float MaxSliderValue =1;
	const float MinSliderValue =0;

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void OnWindowOpen() override;
	virtual void OnWindowClose() override;

protected:
	void SubToSliderEvents();
	void LoadSettings();
	void SaveSettings() const;
	void SetSlidersToSavedValues();
	void SetMixersToSavedValues();
	void UpdateSavedValuesFromSliders(float Value);
	
};



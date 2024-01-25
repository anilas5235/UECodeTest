// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWindowWidget.h"
#include "CodeTest/CustomDataTypes/MyCustomDataTypes.h"
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite) TMap<FName,FAudioSliderData> AudioSliderData;	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) UAudioSave* CurrentSave;
	UPROPERTY(BlueprintReadWrite) TArray<FName> StandardSliders = {FName("Master"),FName("Music"),FName("Effects"),FName("Ambience")};

protected:
	inline static const FString SaveSlotName = FString("AudioWindowSaveSettings");
	const float MaxSliderValue =1;
	const float MinSliderValue =0;

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void OnWindowOpen() override;
	virtual void OnWindowClose() override;

	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") void LoadSettings();
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") void SaveSettings() const;	
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") void SetAudioSliderVolume(FName Name,float Value);
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") float GetAudioSliderVolume(FName Name);

protected:	
	
};



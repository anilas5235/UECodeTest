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
	UPROPERTY() TMap<FName,float> SliderValues;
};

UCLASS()
class CODETEST_API UAudioSettingsWindow : public UUIWindowWidget
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere,BlueprintReadOnly) TArray<FName> SliderNames = {FName("Master"),FName("Music"),FName("Effects"),FName("Ambience")};
	UPROPERTY(EditAnywhere,BlueprintReadOnly) TMap<FName,FAudioSliderData> AudioSliderData;	

protected:
	inline static const FString SaveSlotName = FString("AudioWindowSaveSettings");

	UAudioSave* CurrentSave;

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void OnWindowOpen() override;
	virtual void OnWindowClose() override;

	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") void LoadSettings(const int UserIndex = 0);
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") void SaveSettings(const int UserIndex = 0) const;	
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") void SetAudioSliderVolumePerName(FName Name,float Value);
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") void SetAudioSliderVolumePerIndex(int Index,float Value);
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") float GetAudioSliderVolumePerName(FName Name);
	UFUNCTION(BlueprintCallable,Category="AudioSettingsWindow") float GetAudioSliderVolumePerIndex(int Index);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent) void SetSliderValues();

protected:	
	
};



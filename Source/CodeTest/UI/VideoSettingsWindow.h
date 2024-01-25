// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWindowWidget.h"
#include "VideoSettingsWindow.generated.h"

UCLASS(Abstract)
class CODETEST_API UVideoSettingsWindow : public UUIWindowWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly,Category="VideoSettingsWindow") UGameUserSettings* CurrentGameSettings;
	
	UPROPERTY(BlueprintReadOnly,Category="VideoSettingsWindow") TArray<FIntPoint> PossibleResolutions;
	UPROPERTY(BlueprintReadOnly,Category="VideoSettingsWindow") uint8 CurrentResolutionIndex;	

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeResolution(bool bIncrease = true);
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeWindowMode(bool bIncrease = true);
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeVsync(bool bIncrease = true);
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeOverAllQualityLevel(bool bIncrease = true);
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeFoliageQualityLevel(bool bIncrease = true);

	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ApplyAndSave();
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void LoadSettings();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="VideoSettingsWindow") void UpdateUIText();

	virtual void OnWindowOpen() override;
	virtual void OnWindowClose() override;
};



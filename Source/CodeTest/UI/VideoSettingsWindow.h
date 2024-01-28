// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWindowWidget.h"
#include "VideoSettingsWindow.generated.h"

UENUM(BlueprintType)
enum class EVideoQualityOptions : uint8
{
	OverAll,
	Anti_Aliasing,
	Post_Processing,
	Shadows,
	Global_Illumination,
	Reflections,
	Textures,
	Effects,	
	Foliage,
	Shading,	
};

UCLASS(Abstract)
class CODETEST_API UVideoSettingsWindow : public UUIWindowWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly,Category="VideoSettingsWindow") UGameUserSettings* CurrentGameSettings;	
	UPROPERTY(BlueprintReadOnly,Category="VideoSettingsWindow") TArray<FIntPoint> PossibleResolutions;
	UPROPERTY(BlueprintReadOnly,Category="VideoSettingsWindow") int CurrentResolutionIndex;	

public:
	virtual void NativeConstruct() override;
    virtual void OnWindowOpen() override;
	virtual void OnWindowClose() override;
	
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeResolution(bool bIncrease = true);
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeWindowMode(bool bIncrease = true);
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeVsync(bool bIncrease = true);
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ChangeVideoQualityLevel
	(EVideoQualityOptions Option = EVideoQualityOptions::OverAll,bool bIncrease = true);	

	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void ApplyAndSave();
	UFUNCTION(BlueprintCallable,Category="VideoSettingsWindow") void LoadSettings();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="VideoSettingsWindow") void UpdateUIText();

protected:
	static bool CalculateNewVideoQualityVal(int OldVal ,bool bIncrease, int& NewVal);	
};
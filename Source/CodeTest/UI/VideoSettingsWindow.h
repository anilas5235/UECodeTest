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
	
	UPROPERTY(BlueprintReadOnly) UGameUserSettings* CurrentGameSettings;
	
	UPROPERTY(BlueprintReadOnly) TArray<FIntPoint> PossibleResolutions;
	UPROPERTY(BlueprintReadOnly) uint8 CurrentResolutionIndex;	

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable) void ChangeResolution(bool bIncrease = true);
	UFUNCTION(BlueprintCallable) void ChangeWindowMode(bool bIncrease = true);
	
};



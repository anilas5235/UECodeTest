// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "MyCustomDataTypes.generated.h"

USTRUCT(BlueprintType)
struct  CODETEST_API FAudioSliderData
{
	GENERATED_BODY();

public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite) USlider* Slider;
	UPROPERTY(EditAnywhere,BlueprintReadOnly) USoundClass* SoundClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly) USoundMix* SoundMixer;
};

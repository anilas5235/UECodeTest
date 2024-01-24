// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeTest/Puzzel/WeightButtonComponent.h"
#include "CompButtonRef.generated.h"

USTRUCT(BlueprintType)
struct CODETEST_API FCompButtonRef
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) AActor* ButtonActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ExpectedState;
	UWeightButtonComponent* WeightButtonComponent;
	
};
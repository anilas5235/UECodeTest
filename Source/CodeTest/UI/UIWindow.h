// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UIWindow.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUIWindow : public UInterface
{
	GENERATED_BODY()
};

class CODETEST_API IUIWindow
{
	GENERATED_BODY()
	
public:
	 UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void OnWindowOpen();
	 UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void OnWindowClose();
};

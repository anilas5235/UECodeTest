// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWindowWidget.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWindowActiveStateChanged);

UCLASS(ABSTRACT)
class CODETEST_API UUIWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="UIWindowWidget") bool IsActive;
	UPROPERTY(BlueprintAssignable,BlueprintCallable) FOnWindowActiveStateChanged OnWindowActiveStateChanged;

public:

	UFUNCTION(BlueprintCallable,Category="UIWindowWidget")virtual void OnWindowClose();
	UFUNCTION(BlueprintCallable,Category="UIWindowWidget")virtual void OnWindowOpen();

protected:
	virtual void ChangeActiveState(bool NewState);
	
};

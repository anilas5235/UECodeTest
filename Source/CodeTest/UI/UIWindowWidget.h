// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWindowWidget.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActiveStateChanged);

UCLASS(ABSTRACT)
class CODETEST_API UUIWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="UIWindowWidget") bool IsActive = true;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="UIWindowWidget") UUIWindowWidget* ParentWindowWidget = nullptr;
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="UIWindowWidget") FOnActiveStateChanged OnActiveStateChanged;

	virtual void NativeConstruct() override;

public:	
	UFUNCTION(BlueprintCallable,Category="UIWindowWidget")virtual void OnWindowClose();
	UFUNCTION(BlueprintCallable,Category="UIWindowWidget")virtual void OnWindowOpen();

protected:
	virtual void ChangeActiveState(bool NewState);
	
};

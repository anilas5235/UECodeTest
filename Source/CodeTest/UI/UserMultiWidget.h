// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWindowWidget.h"
#include "Components/WidgetSwitcher.h"
#include "UserMultiWidget.generated.h"

UCLASS(ABSTRACT)
class CODETEST_API UUserMultiWidget : public UUIWindowWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,meta=(BindWidget)) UWidgetSwitcher* MyWidgetSwitcher;

	UPROPERTY(EditAnywhere,BlueprintReadOnly) TArray<TSubclassOf<UUIWindowWidget>> WidgetClasses;

	UPROPERTY(EditAnywhere,BlueprintReadOnly) int StartIndex =-1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) int CurrentlyActiveIndex = -1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) UUIWindowWidget* CurrentlyActiveWidget;		
	
protected:
	TArray<UUIWindowWidget*> CreatedWidgets;

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable) void SwitchWidget(const int Index);
	UFUNCTION(BlueprintCallable) void SwitchToEmpty();

	virtual void OnWindowOpen() override;
	virtual void OnWindowClose() override;	
};

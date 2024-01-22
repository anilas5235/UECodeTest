// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "UserMultiWidget.generated.h"


UCLASS(ABSTRACT)
class CODETEST_API UUserMultiWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,meta=(BindWidget)) UWidgetSwitcher* MyWidgetSwitcher;

	UPROPERTY(EditAnywhere,BlueprintReadOnly) TArray<TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY(EditAnywhere,BlueprintReadOnly) int CurrentlyActiveIndex;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) UWidget* CurrentlyActiveWidget;

protected:
	TArray<UWidget*> CreatedWidgets;

public:
	UFUNCTION(BlueprintCallable) void SwitchWidget(const int Index);

	virtual void NativeConstruct() override;
};

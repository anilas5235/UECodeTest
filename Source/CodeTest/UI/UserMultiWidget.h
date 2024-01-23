// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWindow.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "UserMultiWidget.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWindowActiveStateChanged);

UCLASS(ABSTRACT)
class CODETEST_API UUserMultiWidget : public UUserWidget , public IUIWindow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,meta=(BindWidget)) UWidgetSwitcher* MyWidgetSwitcher;

	UPROPERTY(EditAnywhere,BlueprintReadOnly) TArray<TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY(EditAnywhere,BlueprintReadOnly) int StartIndex =-1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) int CurrentlyActiveIndex = -1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) UWidget* CurrentlyActiveWidget;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) bool IsActive = false;

	UPROPERTY(BlueprintAssignable) FOnWindowActiveStateChanged OnWindowActiveStateChanged;
	
protected:
	TArray<UWidget*> CreatedWidgets;

public:
	UFUNCTION(BlueprintCallable) void SwitchWidget(const int Index);
	UFUNCTION(BlueprintCallable) void SwitchToEmpty();	

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWindowOpen(); virtual void OnWindowOpen_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWindowClose(); virtual void OnWindowClose_Implementation() override;

protected:
	virtual void ChangeActiveState(bool NewState);
	
};

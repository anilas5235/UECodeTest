// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWindowWidget.h"
#include "Components/WidgetSwitcher.h"
#include "UserMultiWidget.generated.h"


UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActiveWindowChanged);

UCLASS(ABSTRACT)
class CODETEST_API UUserMultiWidget : public UUIWindowWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,meta=(BindWidget),Category="UserMultiWidget") UWidgetSwitcher* MyWidgetSwitcher;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UserMultiWidget") TArray<TSubclassOf<UUIWindowWidget>> WidgetClasses;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="UserMultiWidget") UUIWindowWidget* CurrentlyActiveWidget;		

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UserMultiWidget") int StartIndex =-1;
	//UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="UserMultiWidget")
	int CurrentlyActiveIndex = -9999;

	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="UserMultiWidget") FOnActiveWindowChanged OnActiveWindowChanged;

	
protected:
	TArray<UUIWindowWidget*> CreatedWidgets;

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable,Category="UserMultiWidget") void SwitchWidget(const int Index);
	UFUNCTION(BlueprintCallable,Category="UserMultiWidget") void SwitchToEmpty();

	virtual void OnWindowOpen() override;
	virtual void OnWindowClose() override;	
};

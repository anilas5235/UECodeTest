// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/UserMultiWidget.h"
#include "CustomHUDBase.generated.h"

UCLASS(Abstract)
class CODETEST_API ACustomHUDBase : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="CustomHUDBase") TSubclassOf<UUserMultiWidget> MainMultiWidgetClass;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="CustomHUDBase") UUserMultiWidget* MainMultiWidgetRunTimeInstance;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="CustomHUDBase") bool IsMainUIActive = false;

	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="CustomHUDBase") FOnActiveStateChanged OnActiveStateChanged;

	virtual void BeginPlay() override;

	UFUNCTION() void UpdateUIState();

public:
	UFUNCTION(BlueprintCallable,Category="CustomHUDBase") void SwitchMainWidget(const int Index);

protected:
	void SetupWidgets();
	
};

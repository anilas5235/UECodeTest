// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElementalType.h"
#include "Components/ActorComponent.h"
#include "ButtonTriggerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODETEST_API UButtonTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UButtonTriggerComponent();
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Component", meta = (ClampMin = "1.0", ClampMax = "50.0", UIMin = "1.0", UIMax = "50.0")) float Weight = 1.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Component") EElementalType Element;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};

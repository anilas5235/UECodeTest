// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonTriggerComponent.h"
#include "Components/ActorComponent.h"
#include "WeightButtonComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggeredChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODETEST_API UWeightButtonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeightButtonComponent();
	UPROPERTY(VisibleAnywhere,Category="Behaviour",BlueprintReadOnly) bool IsTriggered;
	UPROPERTY(EditAnywhere,Category="Behaviour") float RequiredWeight = 10.f;	
	
	TArray<UButtonTriggerComponent*> ButtonTriggerComponents;
	FOnTriggeredChanged OnButtonTriggeredChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION() void BeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION() void EndOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION() void UpdateWeight();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};

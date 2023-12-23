// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ButtonTriggerComponent.h"
#include "DoorHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODETEST_API UDoorHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorHandler();

	UPROPERTY(VisibleAnywhere,Category="Behaviour",BlueprintReadOnly) bool IsOpening;
	UPROPERTY(EditAnywhere,Category="Behaviour") float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere,Category="Behaviour") float OpenCloseSpeed = 1.f;
	UPROPERTY(EditAnywhere,Category="Behaviour") float ClosingDelay = 2.f;
	
	UPROPERTY(EditAnywhere,Category="Trigger") AActor* OpenTrigger;
	UPROPERTY(EditAnywhere,Category="Trigger") float RequiredWeight = 10.f;	

	TArray<UButtonTriggerComponent*> ButtonTriggerComponents;
	FRotator StartingRotation;
	float CurrentYawAddon;
	float LastTimeTriggered;	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable) virtual void OpenDoor(float DeltaTime);
	UFUNCTION(BlueprintCallable) virtual void CloseDoor(float DeltaTime);
	UFUNCTION() void BeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION() void EndOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION() void UpdateWeight();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};

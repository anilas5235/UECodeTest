// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompButtonRef.h"
#include "Components/ActorComponent.h"
#include "DoorHandler.generated.h"

UENUM(BlueprintType)
enum class EDoorBehaviourType : uint8
{
	DoorType_Hinge      UMETA(DisplayName = "HingeDoor"),
	DoorType_Vertical   UMETA(DisplayName = "VerticalDoor"),
	DoorType_Horizontal UMETA(DisplayName = "HorizontalDoor"),	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODETEST_API UDoorHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorHandler();
	UPROPERTY(EditAnywhere,Category="Behaviour") EDoorBehaviourType DoorType;
	UPROPERTY(EditAnywhere,Category="Behaviour") float OpenCloseSpeed = 1.f;
	UPROPERTY(EditAnywhere,Category="Behaviour") float ClosingDelay = 1.f;
	
	UPROPERTY(EditAnywhere,Category="Behaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Hinge ", EditConditionHides))
	float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere,Category="Behaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Vertical", EditConditionHides))
	float TargetVerticalDifference = 200.f;
	UPROPERTY(EditAnywhere,Category="Behaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Horizontal", EditConditionHides))
	float TargetHorizontalDifference = 200.f;
	UPROPERTY(EditAnywhere,Category="Behaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Horizontal", EditConditionHides))
	bool SlideOnRelativeY = false;
	
	UPROPERTY(EditAnywhere,Category="Sound") USoundBase* OpenDoorSound;
	
	UPROPERTY(VisibleAnywhere,Category="Status",BlueprintReadOnly) bool IsOpening;
	
	UPROPERTY(EditAnywhere,Category="Trigger") TArray<FCompButtonRef> ConnectedButtons;
	
	UStaticMeshComponent* MyDoor;
	FTransform StartingTransform;	
	float CurrentYawAddon;	
	FVector CurrentPositionAddon = FVector(0,0,0);
	float LastTimeTriggered;	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable) virtual void OpenDoor(float DeltaTime);
	UFUNCTION(BlueprintCallable) virtual void CloseDoor(float DeltaTime);	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable) void UpdateTriggeredState();
};

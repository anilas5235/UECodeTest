// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompButtonRef.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum class EDoorBehaviourType : uint8
{
	DoorType_Hinge      UMETA(DisplayName = "HingeDoor"),
	DoorType_Vertical   UMETA(DisplayName = "VerticalDoor"),
	DoorType_Horizontal UMETA(DisplayName = "HorizontalDoor"),	
};


UCLASS()
class CODETEST_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	//Default Comps
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess)) USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess)) UStaticMeshComponent* DoorMesh;

	//Properties	
	UPROPERTY(EditAnywhere,Category="DoorBehaviour") EDoorBehaviourType DoorType;
	UPROPERTY(EditAnywhere,Category="DoorBehaviour") float OpenCloseSpeed = 1.f;
	UPROPERTY(EditAnywhere,Category="DoorBehaviour") float ClosingDelay = 1.f;	
	UPROPERTY(EditAnywhere,Category="DoorBehaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Hinge ", EditConditionHides))
	float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere,Category="DoorBehaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Vertical", EditConditionHides))
	float TargetVerticalDifference = 200.f;
	UPROPERTY(EditAnywhere,Category="DoorBehaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Horizontal", EditConditionHides))
	float TargetHorizontalDifference = 200.f;
	UPROPERTY(EditAnywhere,Category="DoorBehaviour",meta = (EditCondition = "DoorType == EDoorBehaviourType::DoorType_Horizontal", EditConditionHides))
	bool SlideOnRelativeY = false;
	
	
	UPROPERTY(EditAnywhere,Category="DoorBehaviour") TArray<FCompButtonRef> ConnectedButtons;
	UPROPERTY(EditAnywhere,Category="DoorBehaviour",BlueprintReadWrite) bool IsOpening;
	UPROPERTY(EditAnywhere,Category="DoorBehaviour") USoundBase* OpenDoorSound;
	
	
	FTransform StartingTransform;	
	float CurrentYawAddon;	
	FVector CurrentPositionAddon = FVector(0,0,0);
	float LastTimeTriggered;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION() virtual void OpenDoor(float DeltaTime);
	UFUNCTION() virtual void CloseDoor(float DeltaTime);	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void UpdateTriggeredState();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODETEST_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();		
	UPROPERTY(EditAnywhere,Category="Behaviour", BlueprintReadWrite) float GrabbingReach = 200.f;
	UPROPERTY(EditAnywhere,Category="Behaviour", BlueprintReadWrite) float HoldingDistance = 200.f;
	UPhysicsHandleComponent* MyPhysicsHandle = nullptr;
	UCameraComponent* MyCamComponent = nullptr;
	UInputComponent* MyInputComponent = nullptr;

private:
	void InitVars();
	FVector GetLineTraceEndPoint();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable) void Grab();
	UFUNCTION(BlueprintCallable) void ReleaseGrab();
		
};

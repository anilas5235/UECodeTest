// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{	
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	InitVars();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!MyPhysicsHandle || !MyPhysicsHandle-> GrabbedComponent)return;
	if(MyCamComponent)
	{
		const FTransform currentCamTransform =MyCamComponent->GetComponentTransform();
		MyPhysicsHandle->SetTargetLocation(currentCamTransform.GetLocation()+currentCamTransform.Rotator().Vector() * HoldingDistance);
	}
}

void UGrabber::InitVars()
 { 	
 	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
 	if(!MyPhysicsHandle)
 	{
 		UE_LOG(LogTemp, Warning, TEXT("Grabber there is not Phyisics"));
 	} 	
 	MyCamComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
 	if(!MyCamComponent)
 	{
 		UE_LOG(LogTemp, Warning, TEXT("Cam not found"));
 	}
 }

void UGrabber::Grab()
{
	if(!MyPhysicsHandle) return;	

	if(!MyPhysicsHandle-> GrabbedComponent)
	{
		FTransform currentCamTransform =MyCamComponent->GetComponentTransform();		
        	
		FVector TraceEnd = currentCamTransform.GetLocation() + currentCamTransform.Rotator().Vector() * GrabbingReach;  
		
		FHitResult Hit;
		FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());
        
		GetWorld() -> LineTraceSingleByObjectType(OUT Hit,
			currentCamTransform.GetLocation(),TraceEnd,FCollisionObjectQueryParams(ECC_PhysicsBody),TraceParams);
        
		if(Hit.GetActor())
		{			
			MyPhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(),NAME_None,Hit.Location);			
		}	
	}	
}

void UGrabber::ReleaseGrab()
{
	if(!MyPhysicsHandle) return;

	if(const auto grabbedComponent = MyPhysicsHandle-> GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
		grabbedComponent->SetPhysicsLinearVelocity(grabbedComponent->GetPhysicsLinearVelocity() * VelocityScaleAfterRelease);
	}	
}



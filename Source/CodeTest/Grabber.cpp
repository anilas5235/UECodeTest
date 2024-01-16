// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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

	if(MyPhysicsHandle && MyPhysicsHandle-> GrabbedComponent)
	{
		if(MyCamComponent)
		{
			const FTransform currentCamTransform =MyCamComponent->GetComponentTransform();		
        	
			const auto position = currentCamTransform.GetLocation() + currentCamTransform.Rotator().Vector() * HoldingDistance;
		    MyPhysicsHandle->SetTargetLocation(position);
		}
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

FVector UGrabber::GetLineTraceEndPoint()
{
	if(MyCamComponent)
	{
		const FTransform currentCamTransform =MyCamComponent->GetComponentTransform();		
        	
		return  currentCamTransform.GetLocation() + currentCamTransform.Rotator().Vector() * GrabbingReach;
	}

	return FVector(0,0,0);
}

void UGrabber::Grab()
{
	if(!MyPhysicsHandle) return;	

	if(!MyPhysicsHandle-> GrabbedComponent)
	{
		FTransform currentCamTransform =MyCamComponent->GetComponentTransform();		
        	
		FVector TraceEnd = GetLineTraceEndPoint();	      
		
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
	
	if(MyPhysicsHandle-> GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
	}	
}



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
		MyPhysicsHandle->SetTargetLocation(GetLineTraceEndPoint());
	}
}

void UGrabber::InitVars()
 {
 	
 	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
 	if(!MyPhysicsHandle)
 	{
 		UE_LOG(LogTemp, Warning, TEXT("Grabber there is not Phyisics"));
 	}
 	MyInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
 	if(MyInputComponent)
 	{
 		MyInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
 		MyInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseGrab);
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
	//UE_LOG(LogTemp, Warning, TEXT("Grab"));

	if(!MyPhysicsHandle-> GrabbedComponent)
	{
		FTransform currentCamTransform =MyCamComponent->GetComponentTransform();		
        	
		FVector TraceEnd = GetLineTraceEndPoint();	
        
		//DrawDebugLine(GetWorld(), currentCamTransform.GetLocation(),TraceEnd,FColor(1,0,0),false,1.f,0,.5f);
        
		FHitResult Hit;
		FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());
        
		GetWorld() -> LineTraceSingleByObjectType(OUT Hit,
			currentCamTransform.GetLocation(),TraceEnd,FCollisionObjectQueryParams(ECC_PhysicsBody),TraceParams);
        
		if(Hit.GetActor())
		{		
			//UE_LOG(LogTemp, Warning, TEXT(" %s was hit"), *(Hit.GetActor()->GetName()));
			MyPhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(),NAME_None,TraceEnd);			
		}
	}	
}

void UGrabber::ReleaseGrab()
{
	if(!MyPhysicsHandle) return;
	//UE_LOG(LogTemp, Warning, TEXT("Grab Release"));
	
	if(MyPhysicsHandle-> GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
	}	
}



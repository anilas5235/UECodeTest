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
		const FTransform CurrentCamTransform =MyCamComponent->GetComponentTransform();
		MyPhysicsHandle->SetTargetLocation(CurrentCamTransform.GetLocation()+CurrentCamTransform.Rotator().Vector() * HoldingDistance);
	}
}

void UGrabber::InitVars()
 { 	
 	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
 	if(!MyPhysicsHandle){UE_LOG(LogTemp, Warning, TEXT("GrabberComponent: there is no PhyisicsHandle on this Actor"));} 	
 	MyCamComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
 	if(!MyCamComponent){UE_LOG(LogTemp, Warning, TEXT("GrabberComponent: No CameraComponent found on this actor"));}
 }

void UGrabber::Grab() const
{
	FTransform CurrentCamTransform =MyCamComponent->GetComponentTransform();		
        	
	FVector TraceEnd = CurrentCamTransform.GetLocation() + CurrentCamTransform.Rotator().Vector() * GrabbingReach;  
		
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());
        
	GetWorld() -> LineTraceSingleByObjectType(OUT Hit,
		CurrentCamTransform.GetLocation(),TraceEnd,FCollisionObjectQueryParams(ECC_PhysicsBody),TraceParams);
        
	GrabObj(Hit);
}

void UGrabber::GrabObj(const FHitResult HitResult) const
{
	if(!MyPhysicsHandle) return;	
	if(MyPhysicsHandle-> GrabbedComponent) return;
	if(const auto TargetActor = HitResult.GetActor(); !TargetActor) return;
	USceneComponent* Comp = Cast<USceneComponent>(HitResult.GetActor()->FindComponentByClass(USceneComponent::StaticClass()));
	if(Comp && Comp->IsSimulatingPhysics())		
	{
		MyPhysicsHandle->GrabComponentAtLocation(Cast<UPrimitiveComponent>(Comp),NAME_None,HitResult.Location);
	}
}

void UGrabber::ReleaseGrab() const
{
	if(!MyPhysicsHandle) return;

	if(const auto GrabbedComponent = MyPhysicsHandle-> GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
		GrabbedComponent->SetPhysicsLinearVelocity(GrabbedComponent->GetPhysicsLinearVelocity() * VelocityScaleAfterRelease);
	}	
}



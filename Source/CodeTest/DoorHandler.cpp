// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorHandler.h"
#include "ButtonTriggerComponent.h"

// Sets default values for this component's properties
UDoorHandler::UDoorHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorHandler::BeginPlay()
{
	Super::BeginPlay();	
	StartingRotation =GetOwner()->GetActorRotation();
	ActorThatCanTrigger = GetWorld()->GetFirstPlayerController()->GetPawn();

	OpenTrigger->OnActorBeginOverlap.AddDynamic(this,&UDoorHandler::BeginOverlap);
	
	if(ActorThatCanTrigger)
	{
		UE_LOG(LogTemp,Error,TEXT("ActorThatCanTrigger could not be set"))
	}
}

void UDoorHandler::OpenDoor(float DeltaTime)
{	
	CurrentYawAddon =FMath:: Lerp(CurrentYawAddon,TargetYaw,OpenCloseSpeed*DeltaTime);
	FRotator NextRotation = StartingRotation;
	NextRotation.Yaw +=CurrentYawAddon;
	GetOwner()->SetActorRotation(NextRotation);
}

void UDoorHandler::CloseDoor(float DeltaTime)
{	
	CurrentYawAddon =FMath:: Lerp(CurrentYawAddon,0,OpenCloseSpeed * DeltaTime);
	FRotator NextRotation = StartingRotation;
	NextRotation.Yaw +=CurrentYawAddon;
	GetOwner()->SetActorRotation(NextRotation);	
}

void UDoorHandler::BeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{	
	FString name =OtherActor->GetName();
	UE_LOG(LogTemp,Warning,TEXT("Actor: %s was detected"),*name);

	//UActorComponent component = OtherActor->GetComponentByClass(UButtonTriggerComponent :: StaticClass());
}

// Called every frame
void UDoorHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ActorThatCanTrigger)
	{
		IsOpening = OpenTrigger->IsOverlappingActor(ActorThatCanTrigger);
        	
		if(IsOpening)
		{
			OpenDoor(DeltaTime);
			LastTimeTriggered = GetWorld()->GetTimeSeconds();
		}		
		else if(LastTimeTriggered - GetWorld()->GetTimeSeconds() <0)
		{
			CloseDoor(DeltaTime);				
		}
	}
}


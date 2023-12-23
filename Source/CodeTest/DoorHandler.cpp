// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorHandler.h"
#include "ButtonTriggerComponent.h"

// Sets default values for this component's properties
UDoorHandler::UDoorHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	IsOpening = false;
	CurrentYawAddon = 0;
	LastTimeTriggered =0;
}
// Called when the game starts
void UDoorHandler::BeginPlay()
{
	Super::BeginPlay();	
	StartingRotation =GetOwner()->GetActorRotation();	
	
	OpenTrigger->OnActorBeginOverlap.AddDynamic(this,&UDoorHandler::BeginOverlap);
	OpenTrigger->OnActorEndOverlap.AddDynamic(this,&UDoorHandler::EndOverlap);
}

void UDoorHandler::OpenDoor(const float DeltaTime)
{	
	CurrentYawAddon = FMath:: Lerp(CurrentYawAddon,TargetYaw,OpenCloseSpeed*DeltaTime);
	FRotator NextRotation = StartingRotation;
	NextRotation.Yaw += CurrentYawAddon;
	GetOwner()->SetActorRotation(NextRotation);
}

void UDoorHandler::CloseDoor(const float DeltaTime)
{	
	CurrentYawAddon =FMath:: Lerp(CurrentYawAddon,0,OpenCloseSpeed * DeltaTime);
	FRotator NextRotation = StartingRotation;
	NextRotation.Yaw +=CurrentYawAddon;
	GetOwner()->SetActorRotation(NextRotation);	
}

void UDoorHandler::BeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	const auto Component =  Cast<UButtonTriggerComponent>(OtherActor->GetComponentByClass(UButtonTriggerComponent :: StaticClass()));
    if(!Component) return;
	if(!ButtonTriggerComponents.Contains(Component))
    {
	    ButtonTriggerComponents.Add(Component);    	
    }
	UpdateWeight();
}

void UDoorHandler::EndOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	const auto Component =  Cast<UButtonTriggerComponent>(OtherActor->GetComponentByClass(UButtonTriggerComponent :: StaticClass()));
	if(!Component) return;
	if(ButtonTriggerComponents.Contains(Component))	{ButtonTriggerComponents.Remove(Component);}
	if(ButtonTriggerComponents.Num()<1){LastTimeTriggered = GetWorld()->GetTimeSeconds();}
	UpdateWeight();
}

void UDoorHandler::UpdateWeight()
{
	float TotalWeight = 0;	
	for (auto TriggerComponent : ButtonTriggerComponents)
	{
		TotalWeight += TriggerComponent->Weight;
	}

	IsOpening = TotalWeight >= RequiredWeight;
}

// Called every frame
void UDoorHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
        	
	if(IsOpening){OpenDoor(DeltaTime);}		
	else if(GetWorld()->GetTimeSeconds() - LastTimeTriggered >= ClosingDelay){CloseDoor(DeltaTime);}
}


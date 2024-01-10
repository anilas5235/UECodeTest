// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorHandler.h"

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

	MyDoor= GetOwner()->FindComponentByTag<UStaticMeshComponent>("door");
	if(!MyDoor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Door was not found, add tag ´door´ to the static mesh component"), *GetOwner()->GetName());
	}

	for (int i = 0; i < ConnectedButtons.Num(); ++i)
	{
		FCompButtonRef Button = ConnectedButtons[i];
	
		if(!Button.ButtonActor) continue;
		Button.WeightButtonComponent =
			Cast<UWeightButtonComponent>(Button.ButtonActor->GetComponentByClass(UWeightButtonComponent::StaticClass()));
		if(Button.WeightButtonComponent)
		{			
			Button.WeightButtonComponent->OnButtonTriggeredChanged.AddDynamic(this, &UDoorHandler::UpdateTriggeredState);			
		}
		ConnectedButtons[i] = Button;
	}
}

// Called every frame
void UDoorHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
        	
	if(IsOpening){OpenDoor(DeltaTime);}		
	else if(GetWorld()->GetTimeSeconds() - LastTimeTriggered >= ClosingDelay){CloseDoor(DeltaTime);}	
}

void UDoorHandler::UpdateTriggeredState()
{	
	UE_LOG(LogTemp, Warning, TEXT("UpdateState"));
	if(ConnectedButtons.IsEmpty()) return;
	for (const auto Button : ConnectedButtons)
	{
		if(!Button.WeightButtonComponent){continue;}	
		if(Button.WeightButtonComponent->IsTriggered == Button.ExpectedState) {continue;}
		IsOpening = false;
		LastTimeTriggered = GetWorld()->GetTimeSeconds();
		return;
	}
	IsOpening = true;
}

void UDoorHandler::OpenDoor(const float DeltaTime)
{	
	CurrentYawAddon = FMath:: Lerp(CurrentYawAddon,TargetYaw,OpenCloseSpeed*DeltaTime);
	FRotator NextRotation = StartingRotation;
	NextRotation.Yaw += CurrentYawAddon;
	if(MyDoor){MyDoor->SetWorldRotation(NextRotation);}
    else{GetOwner()->SetActorRotation(NextRotation);}
	
}

void UDoorHandler::CloseDoor(const float DeltaTime)
{	
	CurrentYawAddon =FMath:: Lerp(CurrentYawAddon,0,OpenCloseSpeed * DeltaTime);
	FRotator NextRotation = StartingRotation;
	NextRotation.Yaw +=CurrentYawAddon;
	if(MyDoor){MyDoor->SetWorldRotation(NextRotation);}
	else{GetOwner()->SetActorRotation(NextRotation);}
}
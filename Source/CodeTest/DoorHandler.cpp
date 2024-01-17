// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorHandler.h"

#include "Kismet/GameplayStatics.h"

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

	MyDoor= GetOwner()->FindComponentByTag<UStaticMeshComponent>("door");
	if(!MyDoor)
	{
		StartingTransform = GetOwner()->GetTransform();
		UE_LOG(LogTemp, Warning, TEXT("%s : Door was not found, add tag ´door´ to the static mesh component"), *GetOwner()->GetName());
	}
	else
	{
		StartingTransform = MyDoor->GetComponentTransform();
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
        	
	//UE_LOG(LogTemp,Warning,TEXT("Position Addon: %s"),*CurrentPositionAddon.ToCompactString());
	if(IsOpening){OpenDoor(DeltaTime);}		
	else if(GetWorld()->GetTimeSeconds() - LastTimeTriggered >= ClosingDelay){CloseDoor(DeltaTime);}

}

void UDoorHandler::UpdateTriggeredState()
{		
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
	if(OpenDoorSound){UGameplayStatics::SpawnSoundAtLocation(this,OpenDoorSound,GetOwner()->GetActorLocation());}
}

void UDoorHandler::OpenDoor(const float DeltaTime)
{
	switch (DoorType)
	{
	case EDoorBehaviourType::DoorType_Hinge:
		CurrentYawAddon = FMath:: Lerp(CurrentYawAddon,TargetYaw,OpenCloseSpeed*DeltaTime);			
		if(MyDoor){MyDoor->SetRelativeRotation(StartingTransform.Rotator() + FRotator(0,CurrentYawAddon,0));}
		else{GetOwner()->SetActorRotation(StartingTransform.Rotator() + FRotator(0,CurrentYawAddon,0));}
		break;
	case EDoorBehaviourType::DoorType_Vertical:
		CurrentPositionAddon.Z = FMath:: Lerp(CurrentPositionAddon.Z,TargetVerticalDifference,OpenCloseSpeed*DeltaTime);		
		if(MyDoor){MyDoor->SetRelativeLocation(CurrentPositionAddon);}
		else
		{					
			GetOwner()->SetActorLocation(StartingTransform.GetLocation() + CurrentPositionAddon);
		}
		break;
	case EDoorBehaviourType::DoorType_Horizontal:
		if(SlideOnRelativeY)
		{
			CurrentPositionAddon.Y =  FMath:: Lerp(CurrentPositionAddon.Y,TargetHorizontalDifference,OpenCloseSpeed*DeltaTime);			
		}
		else
		{
			CurrentPositionAddon.X =  FMath:: Lerp(CurrentPositionAddon.X,TargetHorizontalDifference,OpenCloseSpeed*DeltaTime);			
		}		
		if(MyDoor){MyDoor->SetRelativeLocation(CurrentPositionAddon);}
		else
		{					
			GetOwner()->SetActorLocation(StartingTransform.GetLocation() + CurrentPositionAddon);
		}
		break;
	default: ;
	}
}

void UDoorHandler::CloseDoor(const float DeltaTime)
{	
	switch (DoorType) {
	case EDoorBehaviourType::DoorType_Hinge:
		CurrentYawAddon =FMath:: Lerp(CurrentYawAddon,0,OpenCloseSpeed * DeltaTime);		
		if(MyDoor){MyDoor->SetRelativeRotation(StartingTransform.Rotator() + FRotator(0,CurrentYawAddon,0));}
		else{GetOwner()->SetActorRotation(StartingTransform.Rotator() + FRotator(0,CurrentYawAddon,0));}
		break;
	case EDoorBehaviourType::DoorType_Vertical:

		CurrentPositionAddon.Z =  FMath:: Lerp(CurrentPositionAddon.Z,0,OpenCloseSpeed*DeltaTime);		
		if(MyDoor){MyDoor->SetRelativeLocation(CurrentPositionAddon);}
		else
		{					
			GetOwner()->SetActorLocation(StartingTransform.GetLocation() + CurrentPositionAddon);
		}		
		break;
	case EDoorBehaviourType::DoorType_Horizontal:
		if(SlideOnRelativeY)
		{
			CurrentPositionAddon.Y =  FMath:: Lerp(CurrentPositionAddon.Y,0,OpenCloseSpeed*DeltaTime);			
		}
		else
		{
			CurrentPositionAddon.X =  FMath:: Lerp(CurrentPositionAddon.X,0,OpenCloseSpeed*DeltaTime);			
		}		
		if(MyDoor){MyDoor->SetRelativeLocation(CurrentPositionAddon);}
		else
		{					
			GetOwner()->SetActorLocation(StartingTransform.GetLocation() + CurrentPositionAddon);
		}
		break;
	default: ;
	}
}
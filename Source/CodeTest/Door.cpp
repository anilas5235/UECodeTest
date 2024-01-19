// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "WeightButtonComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{ 	
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	DefaultSceneRoot->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DoorStaticMesh"));
	DoorMesh->SetupAttachment(DefaultSceneRoot);

	this->Tags.Add(FName("ResetCubes"));	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	StartingTransform = DoorMesh->GetRelativeTransform();	

	for (int i = 0; i < ConnectedButtons.Num(); ++i)
	{
		FCompButtonRef Button = ConnectedButtons[i];
	
		if(!Button.ButtonActor) continue;
		Button.WeightButtonComponent =
			Cast<UWeightButtonComponent>(Button.ButtonActor->GetComponentByClass(UWeightButtonComponent::StaticClass()));
		if(Button.WeightButtonComponent)
		{			
			Button.WeightButtonComponent->OnButtonTriggeredChanged.AddDynamic(this, &ADoor::UpdateTriggeredState);			
		}
		ConnectedButtons[i] = Button;
	}	
}

void ADoor::Tick(float DeltaTime)
 {
 	Super::Tick(DeltaTime);
 
 	if(IsOpening)
 	{ 		
 		OpenDoor(DeltaTime);
 	}		
 	else if(GetWorld()->GetTimeSeconds() - LastTimeTriggered >= ClosingDelay)
 	{
 		CloseDoor(DeltaTime);
 	}
 }


void ADoor::OpenDoor(const float DeltaTime)
{
	switch (DoorType)
	{
	case EDoorBehaviourType::DoorType_Hinge:
		if(CurrentYawAddon - TargetYaw <=0.05f) return;
		CurrentYawAddon = FMath:: Lerp(CurrentYawAddon,TargetYaw,OpenCloseSpeed*DeltaTime);			
		DoorMesh->SetRelativeRotation(StartingTransform.Rotator() + FRotator(0,CurrentYawAddon,0));		
		break;
	case EDoorBehaviourType::DoorType_Vertical:
		if(CurrentPositionAddon.Z - TargetVerticalDifference <=0.05f) return;
		CurrentPositionAddon.Z = FMath:: Lerp(CurrentPositionAddon.Z,TargetVerticalDifference,OpenCloseSpeed*DeltaTime);		
		DoorMesh->SetRelativeLocation(CurrentPositionAddon);		
		break;
	case EDoorBehaviourType::DoorType_Horizontal:
		if(CurrentPositionAddon.Y - TargetHorizontalDifference <=0.05f) return;
		if(SlideOnRelativeY){CurrentPositionAddon.Y =  FMath:: Lerp(CurrentPositionAddon.Y,TargetHorizontalDifference,OpenCloseSpeed*DeltaTime);}
		else{CurrentPositionAddon.X =  FMath:: Lerp(CurrentPositionAddon.X,TargetHorizontalDifference,OpenCloseSpeed*DeltaTime);}		
		DoorMesh->SetRelativeLocation(CurrentPositionAddon);		
		break;
	default: ;
	}
}

void ADoor::CloseDoor(const float DeltaTime)
{
	switch (DoorType) {
	case EDoorBehaviourType::DoorType_Hinge:
		if(abs(CurrentYawAddon) <=0.05f) return;
		CurrentYawAddon =FMath:: Lerp(CurrentYawAddon,0,OpenCloseSpeed * DeltaTime);		
		DoorMesh->SetRelativeRotation(StartingTransform.Rotator() + FRotator(0,CurrentYawAddon,0));		
		break;
	case EDoorBehaviourType::DoorType_Vertical:
        if(abs(CurrentPositionAddon.Z) <=0.05f) return;
		CurrentPositionAddon.Z =  FMath:: Lerp(CurrentPositionAddon.Z,0,OpenCloseSpeed*DeltaTime);		
		DoorMesh->SetRelativeLocation(CurrentPositionAddon);			
		break;
	case EDoorBehaviourType::DoorType_Horizontal:		
		if(SlideOnRelativeY)
		{
			if(abs(CurrentPositionAddon.Y) <=0.05f) return;
			CurrentPositionAddon.Y =  FMath:: Lerp(CurrentPositionAddon.Y,0,OpenCloseSpeed*DeltaTime);
		}
		else
		{
			if(abs(CurrentPositionAddon.X) <=0.05f) return;
			CurrentPositionAddon.X =  FMath:: Lerp(CurrentPositionAddon.X,0,OpenCloseSpeed*DeltaTime);
		}		
		DoorMesh->SetRelativeLocation(CurrentPositionAddon);
		break;
	default: ;
	}
}

void ADoor::UpdateTriggeredState()
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
	if(OpenDoorSound){UGameplayStatics::SpawnSoundAtLocation(this,OpenDoorSound,GetActorLocation());}
}


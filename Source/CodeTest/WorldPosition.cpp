// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();	

	const FString OwnerInstName = GetOwner()->GetName();
	const FString OwnerLabel = GetOwner()->GetActorLabel();
	
	UE_LOG(LogTemp, Error, TEXT("OwnerInstName: %s , OwnerLabel: %s"), *OwnerInstName, * OwnerLabel);
	GEngine -> AddOnScreenDebugMessage(-1,5.f,FColor::Orange, TEXT("Test"));  
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FString worldLocation = GetOwner()->GetActorLocation().ToCompactString();
	const FString OwnerLabel = GetOwner()->GetActorLabel();

	const FString displayText= OwnerLabel+" is at location: "+worldLocation;
	
	GEngine -> AddOnScreenDebugMessage(-1,0.f,FColor::Orange, displayText);
	UE_LOG(LogTemp, Warning, TEXT("%s is at location: %s"),*OwnerLabel ,*worldLocation);
}


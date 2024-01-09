// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightButtonComponent.h"

// Sets default values for this component's properties
UWeightButtonComponent::UWeightButtonComponent()
{	
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWeightButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this,&UWeightButtonComponent::BeginOverlap);
	GetOwner()->OnActorEndOverlap.AddDynamic(this,&UWeightButtonComponent::EndOverlap);	
}


// Called every frame
void UWeightButtonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeightButtonComponent::BeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	const auto Component =  Cast<UButtonTriggerComponent>(OtherActor->GetComponentByClass(UButtonTriggerComponent :: StaticClass()));
	if(!Component) return;
	if(!ButtonTriggerComponents.Contains(Component)) {ButtonTriggerComponents.Add(Component);}
	UpdateWeight();
}

void UWeightButtonComponent::EndOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	const auto Component =  Cast<UButtonTriggerComponent>(OtherActor->GetComponentByClass(UButtonTriggerComponent :: StaticClass()));
	if(!Component) return;
	if(ButtonTriggerComponents.Contains(Component))	{ButtonTriggerComponents.Remove(Component);}	
	UpdateWeight();
}

void UWeightButtonComponent::UpdateWeight()
{
	float TotalWeight = 0;	
	for (auto TriggerComponent : ButtonTriggerComponents){TotalWeight += TriggerComponent->Weight;}
	
	if(const bool bCurrentTriggered =TotalWeight >= RequiredWeight; bCurrentTriggered != IsTriggered)
	{
		IsTriggered = bCurrentTriggered;
		OnButtonTriggeredChanged.Broadcast();
	}	
}


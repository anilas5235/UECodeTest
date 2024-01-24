// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFirstPersonCharacter.h"
#include "Camera/CameraComponent.h"

void ACustomFirstPersonCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
                                   
	UpdateLookAtActor();
}

ACustomFirstPersonCharacter::ACustomFirstPersonCharacter()
{
	CheckedChannels.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	CheckedChannels.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	CheckedChannels.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
}

void ACustomFirstPersonCharacter::UpdateLookAtActor()
{
	if(!GetWorld())return;
	CamTransform =FirstPersonCameraComponent->GetComponentTransform();

	const FVector TraceStart =CamTransform.GetLocation();
	const FVector TraceEnd =CamTransform.GetLocation()+ CamTransform.Rotator().Vector() * MaxDetectionDistance;


	const bool bHit = GetWorld() ->	LineTraceSingleByObjectType(OUT CurrentHitResult,TraceStart,TraceEnd,FCollisionObjectQueryParams(CheckedChannels),TraceParams);

	if(DebugMode)
	{			
		//DrawDebugLineTraceSingle(GetWorld(),TraceStart,TraceEnd,EDrawDebugTrace:: ForOneFrame, bHit, CurrentHitResult,TraceColor,TraceHitColor,1);
	}
	 
	if(AActor* HitActor = CurrentHitResult.GetActor())
	{
		LookAtActor = HitActor;
		LastLookAtActor = HitActor;
	}
	else
	{
		LookAtActor = nullptr;
	}
}



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_FirstPerson/TP_FirstPersonCharacter.h"
#include "CustomFirstPersonCharacter.generated.h"

UCLASS()
class CODETEST_API ACustomFirstPersonCharacter : public ATP_FirstPersonCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="LookAtData") bool DebugMode = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LookAtData")float MaxDetectionDistance = 1000;
	UPROPERTY(EditAnywhere,Category="LookAtData") TArray<TEnumAsByte<EObjectTypeQuery>> CheckedChannels;
	//ReadOnly
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LookAtData")AActor* LookAtActor = nullptr;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LookAtData")AActor* LastLookAtActor = nullptr;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LookAtData")FHitResult CurrentHitResult;

	const FCollisionQueryParams TraceParams =FCollisionQueryParams(FName(TEXT("LooAtTrace")),false,this);	
    const FColor TraceHitColor = FColor(0,255,0);
	const FColor TraceColor = FColor(255,0,0);
	
	
	FTransform CamTransform;


public:
	ACustomFirstPersonCharacter();	

protected:
	virtual void UpdateLookAtActor();
	virtual void Tick(float DeltaSeconds) override;
	
};

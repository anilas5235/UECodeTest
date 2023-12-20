// Copyright Epic Games, Inc. All Rights Reserved.

#include "CodeTestGameMode.h"
#include "CodeTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACodeTestGameMode::ACodeTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

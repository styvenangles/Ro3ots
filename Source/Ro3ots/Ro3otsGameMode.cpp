// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ro3otsGameMode.h"
#include "Ro3otsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARo3otsGameMode::ARo3otsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

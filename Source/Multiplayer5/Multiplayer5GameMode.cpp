// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Multiplayer5GameMode.h"
#include "Multiplayer5Character.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayer5GameMode::AMultiplayer5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

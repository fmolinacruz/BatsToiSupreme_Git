// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatsToiSupreme_RealGameMode.h"
#include "BatsToiSupreme_RealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABatsToiSupreme_RealGameMode::ABatsToiSupreme_RealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/BTInputReceiver.h"

#include "PlayerCommon/BTPlayerController.h"
#include "PlayerCommon/BTUISelectInput.h"
#include "GameModes/BTGameModeBase.h"

// Sets default values
ABTInputReceiver::ABTInputReceiver()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the input component
	BTUISelectionInputComponent = CreateDefaultSubobject<UBTUISelectInput>(TEXT("InputComponent"));
}

void ABTInputReceiver::BeginPlay()
{
	Super::BeginPlay();
}

void ABTInputReceiver::InitializeWithPlayerController(ABTPlayerController* NewPlayerController, int32 PlayerIndex)
{
	if (!NewPlayerController)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NewPlayerController is nullptr"));
		}
		return;
	}
	PlayerController = NewPlayerController;
	CurrentPlayerIndex = PlayerIndex;
}

void ABTInputReceiver::OnCharacterSelected_Implementation(int32 CharacterID)
{
	if (!PlayerController)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnCharacterSelected old is nullptr"));
		}
		return;
	}

	// Assuming your GameMode has a function called 'SpawnPlayerCharacter' that takes a PlayerController, CharacterID, and PlayerIndex
	ABTGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABTGameModeBase>();
	if (!GameMode)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameMode is nullptr"));
		}
		return;
	}

	if (bHasSpawnedPlayer)
	{
		return;
	}

	GameMode->SpawnPlayerCharacter(PlayerController, CharacterID, CurrentPlayerIndex);
	bHasSpawnedPlayer = true;
}

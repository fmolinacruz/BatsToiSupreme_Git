// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/BTInputReceiver.h"

#include "PlayerCommon/BTPlayerController.h"
#include "PlayerCommon/BTUISelectInput.h"
#include "GameModes/BTGameModeBase.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ABTInputReceiver::ABTInputReceiver()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true; 

	// Create the input component
	BTUISelectionInputComponent = CreateDefaultSubobject<UBTUISelectInput>(TEXT("InputComponent"));
}

void ABTInputReceiver::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABTInputReceiver, CurrentPlayerIndex);
	DOREPLIFETIME(ABTInputReceiver, CurrentPlayerController);
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
	CurrentPlayerController = NewPlayerController;
	CurrentPlayerIndex = PlayerIndex;
}

void ABTInputReceiver::OnCharacterSelected(int32 CharacterID)
{
	Server_OnCharacterSelected(CharacterID);
}

void ABTInputReceiver::Server_OnCharacterSelected_Implementation(int32 CharacterID)
{
	Multicast_OnCharacterSelected(CharacterID);
}

void ABTInputReceiver::Multicast_OnCharacterSelected_Implementation(int32 CharacterID)
{
	if (!CurrentPlayerController)
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

	GameMode->SpawnPlayerCharacter(CurrentPlayerController, CharacterID, CurrentPlayerIndex);
	bHasSpawnedPlayer = true;
}

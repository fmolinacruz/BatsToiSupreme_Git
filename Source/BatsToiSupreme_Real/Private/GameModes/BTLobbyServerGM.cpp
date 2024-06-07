// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLobbyServerGM.h"
#include "Engine/World.h"
#include <Utilities/BTLogging.h>
#include <GameModes/BTGameSession.h>
#include "Kismet/GameplayStatics.h"

ABTLobbyServerGM::ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer)
{
	GameSessionClass = ABTGameSession::StaticClass();
}

void ABTLobbyServerGM::BeginPlay()
{
	BTLOG_DISPLAY("[ABTLobbyServerGM] -BeginPlay");

	Super::BeginPlay();
}

void ABTLobbyServerGM::PostLogin(APlayerController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	BTLOG_DISPLAY("[ABTLobbyServerGM] - OnPostLogin: Login New Player %s %i", *NewPlayer->GetName(), GetPlayerCount());

	if (GetPlayerCount() == 1)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FString NewLevelName = FString::Printf(TEXT("%s?game=%s"), "LVMap_TimeSquare_Multi", *GetClass()->GetName());

			// Initiate the server travel to the new level
			World->ServerTravel(NewLevelName);
		}
	}
}

int32 ABTLobbyServerGM::GetPlayerCount() const
{
	// Get the world object
	UWorld* World = GetWorld();
	if (World)
	{
		return World->GetNumPlayerControllers();
	}

	// If the world is not available, return 0
	return 0;
}

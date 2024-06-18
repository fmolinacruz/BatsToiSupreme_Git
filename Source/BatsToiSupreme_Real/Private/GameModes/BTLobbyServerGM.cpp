// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLobbyServerGM.h"
#include "Engine/World.h"
#include <Utilities/BTLogging.h>
#include <GameModes/BTGameSession.h>
#include "Kismet/GameplayStatics.h"

int ABTLobbyServerGM::GetBEPort() const
{
	FString port;
	// Check Mode
	if (FParse::Value(FCommandLine::Get(), TEXT("-Port="), port))
	{
		BTLOG_DISPLAY("BE Port: %s", *port);
	}

	int result = FCString::Atoi(*port);
	return result;
}

ABTLobbyServerGM::ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer)
{
	GameSessionClass = ABTGameSession::StaticClass();
}

void ABTLobbyServerGM::BeginPlay()
{
	BTLOG_DISPLAY("[ABTLobbyServerGM] -BeginPlay");

	Super::BeginPlay();

	BEPort = GetBEPort();
}

void ABTLobbyServerGM::PostLogin(APlayerController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	BTLOG_DISPLAY("[ABTLobbyServerGM] - OnPostLogin: Login New Player %s %i", *NewPlayer->GetName(), GetPlayerCount());

	if (GetPlayerCount() == 1)
	{
		/*UWorld* World = GetWorld();
		if (World)
		{
			FString NewLevelName = TEXT("LVMap_TimeSquare_Multi");
			World->SeamlessTravel(NewLevelName, true);
		}*/
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

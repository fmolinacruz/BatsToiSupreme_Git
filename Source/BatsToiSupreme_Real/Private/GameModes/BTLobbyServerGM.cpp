// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLobbyServerGM.h"
#include "Engine/World.h"
#include <Utilities/BTLogging.h>
#include <GameModes/BTGameSession.h>
#include "Kismet/GameplayStatics.h"
#include "Utilities/BTGameFunctionLibrary.h"
#include <VaRestSubsystem.h>
#include <Utilities/BTHttpRequest.h>
#include <Utilities/GameLiftUtils.h>

void ABTLobbyServerGM::InitGameLift()
{
#if WITH_GAMELIFT
	GameLiftUtils* GameLift = Cast<GameLiftUtils>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), GameLiftUtils::StaticClass()));
	if (GameLift)
	{
		GameLift->Init();
	}
#endif
}

ABTLobbyServerGM::ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer)
{
	GameSessionClass = ABTGameSession::StaticClass();
}

void ABTLobbyServerGM::BeginPlay()
{
	BTLOG_WARNING("[ABTLobbyServerGM] -BeginPlay");

	Super::BeginPlay();
	//Disable gamelift. Change to FleetIq
	//InitGameLift();
}

void ABTLobbyServerGM::PostLogin(APlayerController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	BTLOG_DISPLAY("[ABTLobbyServerGM] - PostLogin: Login New Player %s %i", *NewPlayer->GetName(), GetPlayerCount());

	//if (GetPlayerCount() == 1)
	{
		/*UWorld* World = GetWorld();
		if (World)
		{
			FString NewLevelName = TEXT("LVMap_TimeSquare_Multi");
			World->SeamlessTravel(NewLevelName, true);
		}*/
	}
}

void ABTLobbyServerGM::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	BTLOG_DISPLAY("[ABTLobbyServerGM] - OnPostLogin: Login New Player %s %i", *NewPlayer->GetName(), GetPlayerCount());
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

ABTHttpRequest* ABTLobbyServerGM::GetHttpRequestActor()
{
	if (HttpRequestActor)
		return HttpRequestActor;

	HttpRequestActor = Cast<ABTHttpRequest>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), ABTHttpRequest::StaticClass()));
	return HttpRequestActor;
}

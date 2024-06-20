// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLobbyServerGM.h"
#include "Engine/World.h"
#include <Utilities/BTLogging.h>
#include <GameModes/BTGameSession.h>
#include "Kismet/GameplayStatics.h"
#include "Utilities/BTGameFunctionLibrary.h"
#include <VaRestSubsystem.h>

int ABTLobbyServerGM::GetBEPort() const
{
	FString port;
	// Check Mode
	if (FParse::Value(FCommandLine::Get(), TEXT("-Port="), port))
	{
		BTLOG_WARNING("BE Port: %s", *port);
	}

	int result = FCString::Atoi(*port);
	return result;
}

void ABTLobbyServerGM::OnEOSSessionCreated(FString sessionId)
{
	BTLOG_WARNING("[ABTLobbyServerGM] -OnEOSSessionCreated: %s", *sessionId);
	EosSessionId = sessionId;

	FString BEUrl = BEIp + ":" + BEPort;
	UVaRestJsonObject* JsonObj = NewObject<UVaRestJsonObject>();
	JsonObj->SetStringField(TEXT("sesssionId"), EosSessionId);
	JsonObj->SetStringField(TEXT("BEUrl"), BEUrl);
	UpdateEosSessionData(JsonObj);
}

void ABTLobbyServerGM::Init()
{
	BEPort = FString::FromInt(GetBEPort());
	AccountId = UBTGameFunctionLibrary::GetAccountId();
	ABTGameSession* TempGameSession = Cast<ABTGameSession>(GameSession);
	TempGameSession->OnSessionCreated.AddDynamic(this, &ABTLobbyServerGM::OnEOSSessionCreated);
}

ABTLobbyServerGM::ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer)
{
	GameSessionClass = ABTGameSession::StaticClass();
}

void ABTLobbyServerGM::BeginPlay()
{
	BTLOG_WARNING("[ABTLobbyServerGM] -BeginPlay");

	Super::BeginPlay();
	Init();
	
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

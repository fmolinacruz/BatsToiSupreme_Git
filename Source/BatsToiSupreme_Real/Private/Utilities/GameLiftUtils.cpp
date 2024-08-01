// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/GameLiftUtils.h"
#include "Utilities/BTLogging.h"
#include <Kismet/GameplayStatics.h>
#include <GameModes/BTGameState.h>

GameLiftUtils::GameLiftUtils()
{
}

GameLiftUtils::~GameLiftUtils()
{
}

void GameLiftUtils::Init()
{
	BTLOG_DISPLAY("Initialize GameLift Server !");
	ClientConnectTimeOut = 60;

	GameLiftSDKModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
	if (GameLiftSDKModule == nullptr)
	{
		BTLOG_WARNING("LoadModuleChecked NULL !");
	}

	FString mode;
	// Check Mode
	if (FParse::Value(FCommandLine::Get(), TEXT("-mode="), mode))
	{
	}
	BTLOG_DISPLAY("Initialize GameLift Server ! %s", *mode);
	if (mode == "anywhere")
	{
		InitSDKAnyWhere();
	}
	else
	{
		InitSDKEC2();
	}
	BTLOG_DISPLAY("Initialize GameLift Server 1!");
	// Implement callback function onStartGameSession
	// GameLift sends a game session activation request to the game server
	// and passes a game session object with game properties and other settings.
	// Here is where a game server takes action based on the game session object.
	// When the game server is ready to receive incoming player connections,
	// it invokes the server SDK call ActivateGameSession().
	auto onGameSession = [this](Aws::GameLift::Server::Model::GameSession gameSession) {
		mGameSessionStarted = true;
		FString gameSessionId = FString(gameSession.GetGameSessionId());
		BTLOG_DISPLAY("GameSession Initializing: %s", *gameSessionId);
		GameLiftSDKModule->ActivateGameSession();
		// StartServerTimeOut();
		AsyncTask(ENamedThreads::GameThread, [this] {
			StartServerTimeOut();
		});
	};

	GameLiftProcessParams.OnStartGameSession.BindLambda(onGameSession);

	// Implement callback function OnProcessTerminate
	// GameLift invokes this callback before shutting down the instance hosting this game server.
	// It gives the game server a chance to save its state, communicate with services, etc.,
	// and initiate shut down. When the game server is ready to shut down, it invokes the
	// server SDK call ProcessEnding() to tell GameLift it is shutting down.
	auto onProcessTerminate = [this]() {
		BTLOG_DISPLAY("Game Server Process is terminating");
		GameLiftSDKModule->ProcessEnding();
		mGameSessionStarted = false;
	};

	GameLiftProcessParams.OnTerminate.BindLambda(onProcessTerminate);

	// Implement callback function OnHealthCheck
	// GameLift invokes this callback approximately every 60 seconds.
	// A game server might want to check the health of dependencies, etc.
	// Then it returns health status true if healthy, false otherwise.
	// The game server must respond within 60 seconds, or GameLift records 'false'.
	// In this example, the game server always reports healthy.
	auto onHealthCheck = []() {
		BTLOG_DISPLAY("Performing Health Check");
		return true;
	};
	BTLOG_DISPLAY("Initialize GameLift Server 2!");
	GameLiftProcessParams.OnHealthCheck.BindLambda(onHealthCheck);

	FString logpath;
	// Check Mode
	if (FParse::Value(FCommandLine::Get(), TEXT("-AbsLog="), logpath))
	{
		BTLOG_DISPLAY("GameLift Server LogPath: %s", *logpath);
	}
	FString port;
	// Check Mode
	if (FParse::Value(FCommandLine::Get(), TEXT("-Port="), port))
	{
		BTLOG_DISPLAY("GameLift Server Port: %s", *port);
	}

	GameLiftProcessParams.port = FCString::Atoi(*port);
	TArray<FString> Logfiles;
	Logfiles.Add(logpath);
	GameLiftProcessParams.logParameters = Logfiles;
	GameLiftSDKModule->ProcessReady(GameLiftProcessParams);
}

void GameLiftUtils::InitSDKEC2()
{
	BTLOG_DISPLAY("InitSDKEC2");
	GameLiftSDKModule->InitSDK();
	BTLOG_DISPLAY("InitSDKEC2 DONE");
}

void GameLiftUtils::InitSDKAnyWhere()
{
	BTLOG_DISPLAY("InitSDKAnyWhere");

	// AuthToken returned from the "aws gamelift get-compute-auth-token" API. Note this will expire and require a new call to the API after 15 minutes.
	if (FParse::Value(FCommandLine::Get(), TEXT("-authtoken="), GameLiftServerParams.m_authToken))
	{
	}

	// The Host/compute-name of the GameLift Anywhere instance.
	if (FParse::Value(FCommandLine::Get(), TEXT("-hostid="), GameLiftServerParams.m_hostId))
	{
	}

	// The Anywhere Fleet ID.
	if (FParse::Value(FCommandLine::Get(), TEXT("-fleetid="), GameLiftServerParams.m_fleetId))
	{
	}

	// The WebSocket URL (GameLiftServiceSdkEndpoint).
	if (FParse::Value(FCommandLine::Get(), TEXT("-websocketurl="), GameLiftServerParams.m_webSocketUrl))
	{
	}
	// The PID of the running process
	GameLiftServerParams.m_processId = FString::Printf(TEXT("%d"), GetCurrentProcessId());

	// InitSDK establishes a local connection with GameLift's agent to enable further communication.
	// Use InitSDK(serverParameters) for a GameLift Anywhere fleet.
	// Use InitSDK() for a GameLift managed EC2 fleet.
	GameLiftSDKModule->InitSDK(GameLiftServerParams);
	BTLOG_DISPLAY("InitSDKAnyWhere DONE");
}

void GameLiftUtils::OnGameLiftSessionStart(Aws::GameLift::Server::Model::GameSession ActivatedSession)
{
	const FString GameSessionId = FString(ActivatedSession.GetGameSessionId());
	BTLOG_DISPLAY("OnGameLiftSessionStart: %s", *GameSessionId);

	GameLiftSDKModule->ActivateGameSession();
}

void GameLiftUtils::OnGameLiftSessionUpdate(Aws::GameLift::Server::Model::UpdateGameSession UpdatedSession)
{
	BTLOG_DISPLAY("GameSession Updating!");
}

void GameLiftUtils::OnGameLiftProcessTerminate()
{
	BTLOG_DISPLAY("Game Server Process is terminating!");
	GameLiftSDKModule->ProcessEnding();
}

bool GameLiftUtils::OnGameLiftServerHealthCheck()
{
	BTLOG_DISPLAY("Performing Health Check");
	return true;
}

void GameLiftUtils::StartServerTimeOut()
{
	FString timeout;
	// Check Mode
	if (FParse::Value(FCommandLine::Get(), TEXT("-Timeout="), timeout))
	{
		BTLOG_DISPLAY("GameLift Server timeout: %s", *timeout);
		ClientConnectTimeOut = FCString::Atoi(*timeout);
	}
	// Check Client Connection
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &GameLiftUtils::OnServerTimeOut, ClientConnectTimeOut, true, ClientConnectTimeOut);
}

void GameLiftUtils::OnServerTimeOut()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), FoundActors);
	BTLOG_DISPLAY("OnServerTimeOut %d", FoundActors.Num());

	AGameStateBase* CurGameState = UGameplayStatics::GetGameState(GetWorld());
	if (CurGameState != nullptr)
	{
		ABTGameState* BtGameState = Cast<ABTGameState>(CurGameState);
		if (BtGameState != nullptr)
		{
			// Get the player count
			int32 PlayerCount = CurGameState->PlayerArray.Num();
			if (PlayerCount == 0)
			{
				FGenericPlatformMisc::RequestExit(false);
				GameLiftSDKModule->ProcessEnding();
			}
			// Print the player count
			UE_LOG(LogTemp, Warning, TEXT("Player Count: %d"), PlayerCount);
		}
	}
}

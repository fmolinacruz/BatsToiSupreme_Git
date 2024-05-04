// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BTGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/BTBaseCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Gameplay/BTGameplayManager.h"
#include "PlayerCommon/BTPlayerController.h"
#include "Utilities/BTLogging.h"
#include <GameModes/BTGameState.h>

ABTGameModeBase::ABTGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MainCameraRef(nullptr)
{
	GameLiftSDKModule = nullptr;
	mGameSessionStarted = false;
	ClientConnectTimeOut = 60;
	/*GameLiftProcessParams.OnStartGameSession.BindUObject(this, &ABTGameModeBase::OnGameLiftSessionStart);
	GameLiftProcessParams.OnUpdateGameSession.BindUObject(this, &ABTGameModeBase::OnGameLiftSessionUpdate);
	GameLiftProcessParams.OnTerminate.BindUObject(this, &ABTGameModeBase::OnGameLiftProcessTerminate);
	GameLiftProcessParams.OnHealthCheck.BindUObject(this, &ABTGameModeBase::OnGameLiftServerHealthCheck);
	*/
}

void ABTGameModeBase::BeginPlay()
{
	Super::BeginPlay();
#if WITH_GAMELIFT 
	InitGameLift();
#endif

	InitGameplaySettings();
}

void ABTGameModeBase::InitGameLift()
{
	BTLOG_DISPLAY("Initialize GameLift Server !");

	GameLiftSDKModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
	if (GameLiftSDKModule == nullptr)
	{
		BTLOG_WARNING("LoadModuleChecked NULL !");
	}

	FString mode;
	//Check Mode
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
	auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession) {
		mGameSessionStarted = true;
		FString gameSessionId = FString(gameSession.GetGameSessionId());
		BTLOG_DISPLAY("GameSession Initializing: %s", *gameSessionId);
		GameLiftSDKModule->ActivateGameSession();
		//StartServerTimeOut();
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
	auto onProcessTerminate = [=]() {
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

void ABTGameModeBase::InitSDKEC2()
{
	BTLOG_DISPLAY("InitSDKEC2");
	GameLiftSDKModule->InitSDK();
	BTLOG_DISPLAY("InitSDKEC2 DONE");
}

void ABTGameModeBase::InitSDKAnyWhere()
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

void ABTGameModeBase::InitGameplaySettings()
{
	if (GameplayManagerRef != nullptr)
		return;
	
	GameplayManagerRef = GetWorld()->SpawnActor<ABTGameplayManager>(GameplayManagerClass);
	if (GameplayManagerRef == nullptr)
	{
		BTLOG_ERROR("ABTGameplayManager cannot be spawned!");
	}
}

void ABTGameModeBase::OnGameLiftSessionStart(Aws::GameLift::Server::Model::GameSession ActivatedSession)
{
	const FString GameSessionId = FString(ActivatedSession.GetGameSessionId());
	BTLOG_DISPLAY("OnGameLiftSessionStart: %s", *GameSessionId);

	GameLiftSDKModule->ActivateGameSession();
}

void ABTGameModeBase::OnGameLiftSessionUpdate(Aws::GameLift::Server::Model::UpdateGameSession UpdatedSession)
{
	BTLOG_DISPLAY("GameSession Updating!");
}

void ABTGameModeBase::OnGameLiftProcessTerminate()
{
	BTLOG_DISPLAY("Game Server Process is terminating!");
	GameLiftSDKModule->ProcessEnding();
}

bool ABTGameModeBase::OnGameLiftServerHealthCheck()
{
	BTLOG_DISPLAY("Performing Health Check");
	return true;
}

void ABTGameModeBase::StartServerTimeOut()
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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABTGameModeBase::OnServerTimeOut, ClientConnectTimeOut, true, ClientConnectTimeOut);
}

void ABTGameModeBase::OnServerTimeOut()
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

void ABTGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	BTLOG_DISPLAY("[ABTGameModeBase] - OnPostLogin: Login New Player %s", *NewPlayer->GetName());
	if (bIsLocal)
	{
		return;
	}
	if (GameplayManagerRef == nullptr)
	{
		InitGameplaySettings();
	}

	BTLOG_DISPLAY("[ABTGameModeBase] - OnPostLogin: Login New Player %s", *NewPlayer->GetName());
	if (MainCameraRef == nullptr)
	{
		GetMainCameraRef();
	}
	if (StartSpots.Num() == 0)
	{
		GetStartSpots();
	}

	ABTPlayerController* PC = Cast<ABTPlayerController>(NewPlayer);
	if (!PC)
	{
		BTLOG_WARNING("[ABTGameModeBase] - OnPostLogin: This is not a Player!");
		return;
	}

	BTLOG_WARNING("[ABTGameModeBase] - OnPostLogin: This is a Player!");

	const FVector& Location = StartSpots[CurrentPlayerIndex]->GetActorLocation();
	const FRotator& Rotation = StartSpots[CurrentPlayerIndex]->GetActorRotation();

	ABTInputReceiver* InputReceiver = GetWorld()->SpawnActor<ABTInputReceiver>(InputReceiverClass, Location, Rotation);
	if (InputReceiver)
	{
		PC->Possess(InputReceiver);
		// PC->ClientSetViewTarget(MainCameraRef);

		// Initialize the InputReceiver with the player controller and current player index
		InputReceivers.Add(InputReceiver);
		InputReceiver->InitializeWithPlayerController(PC, CurrentPlayerIndex);

		if (InputReceivers.Num() >= 2)
		{
			InputReceivers[0]->OtherPlayerController = InputReceivers[1]->CurrentPlayerController;
			InputReceivers[1]->OtherPlayerController = InputReceivers[0]->CurrentPlayerController;

			GameplayManagerRef->Player01 = Cast<ABTBaseCharacter>(InputReceivers[0]->CurrentPlayerController->GetCharacter());
			GameplayManagerRef->Player02 = Cast<ABTBaseCharacter>(InputReceivers[1]->CurrentPlayerController->GetCharacter());
		}
	}
	CurrentPlayerIndex++;
}

void ABTGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	BTLOG_DISPLAY("[ABTGameModeBase] - PostLogin: ");
	Super::PostLogin(NewPlayer);
}

void ABTGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	BTLOG_DISPLAY("[ABTGameModeBase] - PostLogin: ");
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void ABTGameModeBase::CheckForSpawningPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex)
{
	BTLOG_DISPLAY("[ABTGameModeBase] - CheckForSpawningPlayerCharacter: ");
	if (!PC)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SpawnPlayerCharacter is nullptr"));
		}
		return;
	}

	// Add player data to the map
	PlayerMap.Add(PlayerIndex, { CharacterID, PC });

	// Check if there are at least 2 players
	if (PlayerMap.Num() >= 2)
	{
		for (const auto& Pair : PlayerMap)
		{
			StartSpawningPlayerCharacter(Pair.Value.Controller, Pair.Value.CharacterID, Pair.Key);
		}

		for (const ABTInputReceiver* InputReceiver : InputReceivers)
		{
			if (InputReceiver)
			{
				InputReceiver->CurrentPlayerController->Client_TurnOffCharacterSelectMenu();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MenuWidgetRefCPP is nullptr"));
			}
		}
	}
}

void ABTGameModeBase::StartSpawningPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("SpawnPlayerCharacter with PlayerIndex: %d"), PlayerIndex));
	}

	// Retrieve the spawn location and rotation from the start spots array
	const FVector& Location = StartSpots[PlayerIndex]->GetActorLocation();
	const FRotator& Rotation = StartSpots[PlayerIndex]->GetActorRotation();

	// Spawn the player character using the selected CharacterID
	// For simplicity, this example uses the same CharacterClass for all IDs
	ABTBaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABTBaseCharacter>(CharacterClass, Location, Rotation);
	if (SpawnedCharacter)
	{
		// PC->UnPossess();
		PC->Possess(SpawnedCharacter);
		PC->ClientSetViewTarget(MainCameraRef);

		PlayerCharacters.Add(SpawnedCharacter);
		SpawnedCharacter->SetPlayerIndex(PlayerIndex);
		SpawnedCharacter->SetCharacterID(CharacterID);

		// Set enemies if there are at least 2 players
		// (Assuming PlayerCharacters array is sorted by player index)
		if (PlayerCharacters.Num() >= 2)
		{
			PlayerCharacters[0]->BTEnemy = PlayerCharacters[1];
			PlayerCharacters[1]->BTEnemy = PlayerCharacters[0];
		}
	}
}

void ABTGameModeBase::RestorePlayerCharacter(int PlayerIndex)
{
	// Remove player data to the map
	PlayerMap.Remove(PlayerIndex);
}

void ABTGameModeBase::GetMainCameraRef()
{
	TArray<AActor*> AllCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CameraClass, AllCameras);
	if (AllCameras.Num() == 0)
	{
		BTLOG_ERROR("[ABTGameModeBase] - BeginPlay: There's no main camera setup!");
		return;
	}

	MainCameraRef = AllCameras[0];
}

void ABTGameModeBase::GetStartSpots()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), StartSpots);
}

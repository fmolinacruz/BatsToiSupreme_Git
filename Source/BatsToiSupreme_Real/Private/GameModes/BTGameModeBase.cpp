// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BTGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/BTBaseCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerCommon/BTPlayerController.h"
#include "Utilities/BTLogging.h"

ABTGameModeBase::ABTGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MainCameraRef(nullptr)
{
	GameLiftSDKModule = nullptr;
	GameLiftProcessParams.OnStartGameSession.BindUObject(this, &ABTGameModeBase::OnGameLiftSessionStart);
	GameLiftProcessParams.OnUpdateGameSession.BindUObject(this, &ABTGameModeBase::OnGameLiftSessionUpdate);
	GameLiftProcessParams.OnTerminate.BindUObject(this, &ABTGameModeBase::OnGameLiftProcessTerminate);
	GameLiftProcessParams.OnHealthCheck.BindUObject(this, &ABTGameModeBase::OnGameLiftServerHealthCheck);
	
}

void ABTGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	InitGameLift();
}

void ABTGameModeBase::InitGameLift()
{
	BTLOG_DISPLAY("Initialize GameLift Server !");

	GameLiftSDKModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

	FString mode;
	//Check Mode
	if (FParse::Value(FCommandLine::Get(), TEXT("-mode="), mode))
	{
		
	}
	if (mode == "anywhere")
	{
		InitSDKAnyWhere();
	}
	else
	{
		InitSDKEC2();
	}

	GameLiftSDKModule->InitSDK();

	GameLiftProcessParams.port = 7777;
	
	TArray<FString> Logfiles;
	Logfiles.Add(TEXT("GameLiftServer/Saved/Logs/GameLiftTest.log"));
	GameLiftProcessParams.logParameters = Logfiles;
	
	BTLOG_DISPLAY("Calling Process Ready");
	GameLiftSDKModule->ProcessReady(GameLiftProcessParams);
}

void ABTGameModeBase::InitSDKEC2()
{
	BTLOG_DISPLAY("InitSDKEC2");
	GameLiftSDKModule->InitSDK();
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
}

void ABTGameModeBase::OnGameLiftSessionStart(Aws::GameLift::Server::Model::GameSession ActivatedSession)
{
	const FString GameSessionId = FString(ActivatedSession.GetGameSessionId());
	BTLOG_DISPLAY("GameSession Initializing: %s", *GameSessionId);

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

void ABTGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if (bIsLocal)
	{
		return;
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
		}
	}
	CurrentPlayerIndex++;
}

void ABTGameModeBase::CheckForSpawningPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex)
{
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

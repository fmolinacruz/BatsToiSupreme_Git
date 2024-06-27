// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTGameSession.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineStatsInterface.h"

// Dedicated Server Only

ABTGameSession::ABTGameSession()
{
	// Tutorial 3: Including constructor here for clarity. Nothing added in derived class for this tutorial.
}

bool ABTGameSession::ProcessAutoLogin()
{
	// Tutorial 3: Overide base function as players need to login before joining the session. We don't want to call AutoLogin on server.
	return true;
}

FString ABTGameSession::ApproveLogin(const FString& Options)
{
	if (IsRunningDedicatedServer())
	{
		// If the server is full return an error. Catching the error on the client is NOT implemented in this sample.
		// See UCommonSessionSubsystem::Initialize in the Lyra project for an example.
		Super::ApproveLogin(Options);
		return NumberOfPlayersInSession == MaxNumberOfPlayersInSession ? "FULL" : "";
	}
	else
	{
		return "";
	}
}

void ABTGameSession::BeginPlay()
{
	// Tutorial 3: Overide base function to create session when running as dedicated server
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ABTGameSession::BeginPlay"));
	if (IsRunningDedicatedServer() && !bSessionExists) // Only create a session if running as a dedicated server and session doesn't exist
	{
		CreateSession("KeyName", "KeyValue"); // Should parametrized Key/Value pair for custom attribute
	}
}

void ABTGameSession::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Tutorial 3: Overide base function to destroy session at end of play. This happens on both dedicated server and client
	Super::EndPlay(EndPlayReason);
	DestroySession();
}

void ABTGameSession::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumberOfPlayersInSession++; // Keep track of players registered in session

	// Tutorial 3: Add code here if you need to do anything else after a player joins the dedicated server
}

void ABTGameSession::NotifyLogout(const APlayerController* ExitingPlayer)
{
	// Tutorial 3: Overide base function to handle players leaving EOS Session.
	Super::NotifyLogout(ExitingPlayer); // This calls UnregisterPlayer

	// When players leave the dedicated server we need to check how many players are left. If 0 players are left, session is destroyed.
	if (IsRunningDedicatedServer())
	{
		NumberOfPlayersInSession--; // Keep track of players as they leave

		// No one left in server - end session if session is InProgress
		if (NumberOfPlayersInSession == 0)
		{
			IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
			IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

			Session->GetSessionState(SessionName);
			if (Session->GetSessionState(SessionName) == EOnlineSessionState::InProgress)
			{
				EndSession();
			}
		}
	}
	else
	{
		// This isn't "handling" the error when the server is full, just a log to help keep track of the flow.
		UE_LOG(LogTemp, Log, TEXT("Player is leaving the dedicated server. This may be a kick because the server is full if the player didn't leave intentionally."))
	}
}

void ABTGameSession::CreateSession(FName KeyName, FString KeyValue) // Dedicated Server Only
{
	// Tutorial 3: This function will create an EOS Session.
	UE_LOG(LogTemp, Warning, TEXT("ABTGameSession::CreateSession"));
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface.

	// Bind delegate to callback function
	CreateSessionDelegateHandle =
		Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleCreateSessionCompleted));

	// Set session settings
	TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
	SessionSettings->NumPublicConnections = MaxNumberOfPlayersInSession; // We will test our sessions with 2 players to keep things simple
	SessionSettings->bShouldAdvertise = true;							 // This creates a public match and will be searchable. This will set the session as joinable via presence.
	SessionSettings->bUsesPresence = false;								 // No presence on dedicated server. This requires a local user.
	SessionSettings->bAllowJoinViaPresence = false;						 // superset by bShouldAdvertise and will be true on the backend
	SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;			 // superset by bShouldAdvertise and will be true on the backend
	SessionSettings->bAllowInvites = false;								 // Allow inviting players into session. This requires presence and a local user.
	SessionSettings->bAllowJoinInProgress = false;						 // Once the session is started, no one can join.
	SessionSettings->bIsDedicated = true;								 // Session created on dedicated server.
	SessionSettings->bUseLobbiesIfAvailable = false;					 // This is an EOS Session not an EOS Lobby as they aren't supported on Dedicated Servers.
	SessionSettings->bUseLobbiesVoiceChatIfAvailable = false;
	SessionSettings->bUsesStats = true; // Needed to keep track of player stats.

	// This custom attribute will be used in searches on GameClients.
	SessionSettings->Settings.Add(KeyName, FOnlineSessionSetting((KeyValue), EOnlineDataAdvertisementType::ViaOnlineService));

	// Create session.
	UE_LOG(LogTemp, Warning, TEXT("Creating session..."));

	if (!Session->CreateSession(0, SessionName, *SessionSettings))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
		CreateSessionDelegateHandle.Reset();
	}
}

void ABTGameSession::HandleCreateSessionCompleted(FName EOSSessionName, bool bWasSuccessful) // Dedicated Server Only
{
	// Tutorial 3: This function is triggered via the callback we set in CreateSession once the session is created (or there is a failure to create)
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface.

	// Nothing special here, simply log that the session is created.
	if (bWasSuccessful)
	{
		FString sessionId = Session->GetNamedSession(EOSSessionName)->GetSessionIdStr();
		bSessionExists = true;
		OnSessionCreated.Broadcast(sessionId);
		OnSessionCreated.Clear();
		UE_LOG(LogTemp, Warning, TEXT("Session: %s Created 1! %s"), *EOSSessionName.ToString(), *sessionId);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
	}

	// Clear our handle and reset the delegate.
	Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
	CreateSessionDelegateHandle.Reset();

}

void ABTGameSession::RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite)
{
	// Tutorial 3: Override base function to register player in EOS Session
	Super::RegisterPlayer(NewPlayer, UniqueId, bWasFromInvite);
	UE_LOG(LogTemp, Warning, TEXT("Player registered in EOS Session! -- %s"), *NewPlayer->GetName());
	if (IsRunningDedicatedServer()) // Only run this on the dedicated server
	{
		IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
		IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface.

		// Bind delegate to callback function
		RegisterPlayerDelegateHandle =
			Session->AddOnRegisterPlayersCompleteDelegate_Handle(FOnRegisterPlayersCompleteDelegate::CreateUObject(
				this,
				&ThisClass::HandleRegisterPlayerCompleted));

		if (!Session->RegisterPlayer(SessionName, *UniqueId, false))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Register Player!"));
			Session->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayerDelegateHandle);
			RegisterPlayerDelegateHandle.Reset();
		}
	}
}

void ABTGameSession::HandleRegisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{
	// Tutorial 3: This function is triggered via the callback we set in RegisterPlayer once the player is registered (or there is a failure)
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bWasSuccesful)
	{
		UE_LOG(LogTemp, Log, TEXT("Player registered in EOS Session!"));
		if (NumberOfPlayersInSession == MaxNumberOfPlayersInSession)
		{
			StartSession(); // Start the session when we've reached the max number of players
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to register player! (From Callback)"));
	}

	// Clear and reset delegates
	Session->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayerDelegateHandle);
	RegisterPlayerDelegateHandle.Reset();
}

void ABTGameSession::UnregisterPlayer(const APlayerController* ExitingPlayer)
{
	// Tutorial 3: Override base function to Unregister player in EOS Session
	Super::UnregisterPlayer(ExitingPlayer);

	// Only need to unregisted the player in the EOS Session on the Server
	if (IsRunningDedicatedServer())
	{
		IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
		IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
		IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

		if (ExitingPlayer->PlayerState) // If the player leaves ungracefully this could be null
		{
			// Bind delegate to callback function
			UnregisterPlayerDelegateHandle =
				Session->AddOnUnregisterPlayersCompleteDelegate_Handle(FOnUnregisterPlayersCompleteDelegate::CreateUObject(
					this,
					&ThisClass::HandleUnregisterPlayerCompleted));

			if (!Session->UnregisterPlayer(SessionName, *ExitingPlayer->PlayerState->UniqueId))
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
				Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
				UnregisterPlayerDelegateHandle.Reset();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
		}
	}
}

void ABTGameSession::HandleUnregisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{
	// Tutorial 3: This function is triggered via the callback we set in UnregisterPlayer once the player is unregistered (or there is a failure).

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Just log, clear and reset delegate.
	if (bWasSuccesful)
	{
		UE_LOG(LogTemp, Log, TEXT("Player unregistered in EOS Session!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to unregister player! (From Callback)"));
	}
	Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
	UnregisterPlayerDelegateHandle.Reset();
}

void ABTGameSession::StartSession()
{
	// Tutorial 3: This function is called once all players are registered. It will mark the EOS Session as started.
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Bind delegate to callback function
	StartSessionDelegateHandle =
		Session->AddOnStartSessionCompleteDelegate_Handle(FOnStartSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleStartSessionCompleted));

	if (!Session->StartSession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to start session!"));
		Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
		StartSessionDelegateHandle.Reset();
	}
}

void ABTGameSession::HandleStartSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
	// Tutorial 3: This function is triggered via the callback we set in StartSession once the session is started (or there is a failure).
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Just log, clear and reset delegate.
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session Started!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to start session! (From Callback)"));
	}

	Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
	StartSessionDelegateHandle.Reset();
}

void ABTGameSession::EndSession()
{
	// Tutorial 3: This function is called once all players have left the session. It will mark the EOS Session as ended.
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Bind delegate to callback function
	EndSessionDelegateHandle =
		Session->AddOnEndSessionCompleteDelegate_Handle(FOnEndSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleEndSessionCompleted));

	if (!Session->EndSession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to end session!"));
		Session->ClearOnEndSessionCompleteDelegate_Handle(EndSessionDelegateHandle);
		EndSessionDelegateHandle.Reset();
	}
}

void ABTGameSession::HandleEndSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
	// Tutorial 3: This function is triggered via the callback we set in EndSession once the session is ended (or there is a failure).
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Just log, clear and reset delegate.
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session ended!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to end session! (From Callback)"));
	}

	Session->ClearOnEndSessionCompleteDelegate_Handle(EndSessionDelegateHandle);
	EndSessionDelegateHandle.Reset();
}

void ABTGameSession::DestroySession()
{
	// Tutorial 3: Called when EndPlay() is called. This will destroy the EOS Session which will remove it from the EOS backend.

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	DestroySessionDelegateHandle =
		Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleDestroySessionCompleted));

	if (!Session->DestroySession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session.")); // Log to the UE logs that we are trying to log in.
		Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
		DestroySessionDelegateHandle.Reset();
	}
}

void ABTGameSession::HandleDestroySessionCompleted(FName EOSSessionName, bool bWasSuccesful)
{
	// Tutorial 3: This function is triggered via the callback we set in DestroySession once the session is destroyed (or there is a failure).

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bWasSuccesful)
	{
		bSessionExists = false; // Mark that the session doesn't exist. This way next time BeginPlay is called a new session will be created.
		UE_LOG(LogTemp, Log, TEXT("Destroyed session succesfully."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session."));
	}

	Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
	DestroySessionDelegateHandle.Reset();
}

void ABTGameSession::OnTest()
{
	UE_LOG(LogTemp, Warning, TEXT("Test Session."));
}

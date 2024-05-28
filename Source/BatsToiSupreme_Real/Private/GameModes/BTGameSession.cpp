// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTGameSession.h"
#include <OnlineSubsystem.h>

// Dedicated Server Only
void ABTGameSession::CreateSession(FName KeyName, FString KeyValue)
{
	// Tutorial 3: This function will create an EOS Session.

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
	UE_LOG(LogTemp, Log, TEXT("Creating session..."));

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
		bSessionExists = true;
		UE_LOG(LogTemp, Log, TEXT("Session: %s Created!"), *EOSSessionName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
	}

	// Clear our handle and reset the delegate.
	Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
	CreateSessionDelegateHandle.Reset();
}

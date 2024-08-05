// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include <Utilities/EOSUtils.h>

#include "BTGameSession.generated.h"

/**
 * Acts as a game-specific wrapper around the session interface.
 The game code makes calls to this when it needs to interact with the session interface.
 A game session exists only the server, while running an online game
 */
UCLASS()
class BATSTOISUPREME_REAL_API ABTGameSession : public AGameSession
{
	GENERATED_BODY()
protected:
	// Class constructor. We won't use this in this tutorial.
	ABTGameSession();

	// Function called when play begins.
	virtual void BeginPlay();

	// Function called when play ends. We are using this to destroy session.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	// This function exists on the base class AGameSession. We want to override it so we don't try to login from a dedicated server.
	virtual bool ProcessAutoLogin();

	// This function will be used to check if our session is full . It's better to check when a player joins rather than seeing if RegisterPlayer fails as it is async.
	virtual FString ApproveLogin(const FString& Options);

	// Function called when players join dedicated server. Not used in this tutorial.
	virtual void PostLogin(APlayerController* NewPlayer);

	// Function called when players leave the dedicated server. Trigger UnregisterPlayer from base class and used to End Sesion.
	virtual void NotifyLogout(const APlayerController* ExitingPlayer);

	// Function to register our players in the EOS Session.
	virtual void RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite = false);

	// Callback function. This function will run when registering the player compeletes.
	void HandleRegisterPlayerCompleted(FName SessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful);

	// Delegate to bind callback event for register player.
	FDelegateHandle RegisterPlayerDelegateHandle;

	// Function to unregister our players in the EOS Session.
	virtual void UnregisterPlayer(const APlayerController* ExitingPlayer);

	// Callback function. This function will run when unregistering the player compeletes.
	void HandleUnregisterPlayerCompleted(FName SessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful);

	// Delegate to bind callback event for unregister player.
	FDelegateHandle UnregisterPlayerDelegateHandle;

public:
	
private:	

	//Init EOS
	UFUNCTION()
	void InitEOS();

	UFUNCTION()
	void OnEOSSessionCreated(FString sessionId);

	//Update Host Data For Client
	UFUNCTION()
	void UpdateEosSessionData(FString sessionId, FString BEUrl);
	UFUNCTION()
	void OnUpdateEosSessionDataCompleted(UVaRestRequestJSON* Request);

	//Get Cloud Host Ip
	UFUNCTION()
	void RequestCloudHostIp();

	//Get Cloud Host Response
	UFUNCTION()
	void OnGetCloudHostIpCompleted(UVaRestRequestJSON* Request);

	// Hardcoding the max number of players in a session.
	const int MaxNumberOfPlayersInSession = 2;

	// Variable to keep track of the number of players in a session.
	int NumberOfPlayersInSession = 0;

	// Used to keep track if the session exists or not.
	bool bSessionExists = false;

	AEOSUtils* EOSUtilsObj;
	FString EOSSessionId;
};

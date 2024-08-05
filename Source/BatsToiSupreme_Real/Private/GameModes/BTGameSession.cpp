// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTGameSession.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include <Utilities/BTGameFunctionLibrary.h>
#include <Utilities/BTLogging.h>
#include <GameModes/BTLobbyServerGM.h>
#include <Utilities/BTHttpRequest.h>

// Dedicated Server Only

ABTGameSession::ABTGameSession()
{
	// Including constructor here for clarity. Nothing added in derived class for this tutorial.
}

bool ABTGameSession::ProcessAutoLogin()
{
	// Overide base function as players need to login before joining the session. We don't want to call AutoLogin on server.
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
	// Overide base function to create session when running as dedicated server
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ABTGameSession::BeginPlay"));
	InitEOS();
}

void ABTGameSession::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Overide base function to destroy session at end of play. This happens on both dedicated server and client
	Super::EndPlay(EndPlayReason);
#if WITH_EOS_SESSION
	if (EOSUtilsObj)
	{
		EOSUtilsObj->DestroySession();
	}
#endif
}

void ABTGameSession::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumberOfPlayersInSession++; // Keep track of players registered in session

	// Add code here if you need to do anything else after a player joins the dedicated server
}

void ABTGameSession::NotifyLogout(const APlayerController* ExitingPlayer)
{
	// Overide base function to handle players leaving EOS Session.
	Super::NotifyLogout(ExitingPlayer); // This calls UnregisterPlayer
#if WITH_EOS_SESSION
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
				if (EOSUtilsObj)
				{
					EOSUtilsObj->EndSession();
				}
			}
		}
	}
	else
	{
		// This isn't "handling" the error when the server is full, just a log to help keep track of the flow.
		UE_LOG(LogTemp, Log, TEXT("Player is leaving the dedicated server. This may be a kick because the server is full if the player didn't leave intentionally."))
	}
#endif
}

void ABTGameSession::RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite)
{
	// Override base function to register player in EOS Session
	Super::RegisterPlayer(NewPlayer, UniqueId, bWasFromInvite);
	UE_LOG(LogTemp, Warning, TEXT("Player registered in EOS Session! -- %s"), *NewPlayer->GetName());
#if WITH_EOS_SESSION
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
#endif
}

void ABTGameSession::HandleRegisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{
	// This function is triggered via the callback we set in RegisterPlayer once the player is registered (or there is a failure)
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bWasSuccesful)
	{
		UE_LOG(LogTemp, Log, TEXT("Player registered in EOS Session!"));
		if (NumberOfPlayersInSession == MaxNumberOfPlayersInSession)
		{
			if (EOSUtilsObj)
			{
				EOSUtilsObj->StartSession();
			}
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
	// Override base function to Unregister player in EOS Session
	Super::UnregisterPlayer(ExitingPlayer);

#if WITH_EOS_SESSION
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

			//TODO: Fix compiler bug
			//if (!Session->UnregisterPlayer(SessionName, *ExitingPlayer->PlayerState->UniqueId))
			//{
			//	UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
			//	Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
			//	UnregisterPlayerDelegateHandle.Reset();
			//}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
		}
	}
#endif
}

void ABTGameSession::HandleUnregisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{
	// This function is triggered via the callback we set in UnregisterPlayer once the player is unregistered (or there is a failure).

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

void ABTGameSession::InitEOS()
{
#if WITH_EOS_SESSION
	if (IsRunningDedicatedServer() && !bSessionExists) // Only create a session if running as a dedicated server and session doesn't exist
	{
		EOSUtilsObj = Cast<AEOSUtils>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), AEOSUtils::StaticClass()));
		if (EOSUtilsObj)
		{
			EOSUtilsObj->OnSessionCreated.AddDynamic(this, &ABTGameSession::OnEOSSessionCreated);
			//TODO: Pass correct param
			EOSUtilsObj->CreateSession("KeyName", "KeyValue");
		}
	}
#endif
}


void ABTGameSession::OnEOSSessionCreated(FString sessionId)
{
	BTLOG_WARNING("[ABTLobbyServerGM] -OnEOSSessionCreated: %s", *sessionId);
	bSessionExists = true;
	// Init Port
	EOSSessionId = sessionId;
	if (UBTGameFunctionLibrary::IsLanHost())
	{
		FString BEPort = FString::FromInt(UBTGameFunctionLibrary::GetBEPort());
		FString BEIp = UBTGameFunctionLibrary::GetLocalIP();
		FString BEUrl = BEIp + ":" + BEPort;
		UpdateEosSessionData(EOSSessionId, BEUrl);
	}
	else
	{
		//get Cloud Host Ip
		RequestCloudHostIp();
	}
}

void ABTGameSession::UpdateEosSessionData(FString sessionId, FString BEUrl)
{
	UE_LOG(LogTemp, Error, TEXT("UpdateEosSessionData: %s %s"), *sessionId, *BEUrl);
	UVaRestJsonObject* JsonObj = NewObject<UVaRestJsonObject>();
	JsonObj->SetStringField(TEXT("sessionId"), sessionId);
	UVaRestJsonObject* JsonDataObj = NewObject<UVaRestJsonObject>();
	JsonDataObj->SetStringField(TEXT("BEUrl"), BEUrl);
	JsonObj->SetObjectField(TEXT("data"), JsonDataObj);

	// Get Cloud Host IP
	ABTHttpRequest* HttpRequestActor = Cast<ABTHttpRequest>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), ABTHttpRequest::StaticClass()));
	if (HttpRequestActor)
	{
		UVaRestRequestJSON* Request = HttpRequestActor->CreateRequest(EVaRestRequestVerb::POST, EVaRestRequestContentType::json);
		Request->OnRequestComplete.AddDynamic(this, &ABTGameSession::OnUpdateEosSessionDataCompleted);
		Request->SetHeader(TEXT("x-api-key"), UBTGameFunctionLibrary::XAPIKey);
		Request->GetRequestObject()->MergeJsonObject(JsonObj, true);
		Request->ProcessURL(UBTGameFunctionLibrary::GetUpdateSessionDataURL());

	}
}

void ABTGameSession::OnUpdateEosSessionDataCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("OnUpdateEosSessionDataCompleted Response: %s"), *ResponseContent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnUpdateEosSessionDataCompleted: Request failed"));
	}
}

void ABTGameSession::RequestCloudHostIp()
{
	ABTHttpRequest* HttpRequestActor = Cast<ABTHttpRequest>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), ABTHttpRequest::StaticClass()));
	if (HttpRequestActor)
	{
		// Get Cloud Host IP
		UVaRestRequestJSON* Request = HttpRequestActor->CreateRequest(EVaRestRequestVerb::GET, EVaRestRequestContentType::x_www_form_urlencoded_url);
		Request->OnRequestComplete.AddDynamic(this, &ABTGameSession::OnGetCloudHostIpCompleted);
		Request->ProcessURL(UBTGameFunctionLibrary::Ipifp);
	}
}

void ABTGameSession::OnGetCloudHostIpCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleGetDataCompleted Response: %s"), *ResponseContent);

		//Update Data
		FString BEPort = FString::FromInt(UBTGameFunctionLibrary::GetBEPort());
		FString BEIp = Request->GetResponseObject()->GetString();
		FString BEUrl = BEIp + ":" + BEPort;
		UpdateEosSessionData(EOSSessionId, BEUrl);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnGetCloudHostIpCompleted: Request failed"));
	}
}

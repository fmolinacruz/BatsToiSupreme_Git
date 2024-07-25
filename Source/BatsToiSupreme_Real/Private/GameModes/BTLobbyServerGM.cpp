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
	JsonObj->SetStringField(TEXT("sessionId"), EosSessionId);
	UVaRestJsonObject* JsonDataObj = NewObject<UVaRestJsonObject>();
	JsonDataObj->SetStringField(TEXT("BEUrl"), BEUrl);
	JsonObj->SetObjectField(TEXT("data"), JsonDataObj);
	UpdateEosSessionData(JsonObj);
}

void ABTLobbyServerGM::InitEOS()
{
	//Init Port
	BEPort = FString::FromInt(GetBEPort());
	if (UBTGameFunctionLibrary::IsLanHost())
	{
		BEIp = UBTGameFunctionLibrary::GetLocalIP();		
	}
	else
	{
		RequestCloudHostIp();
	}

	AccountId = UBTGameFunctionLibrary::GetAccountId();
	ABTGameSession* TempGameSession = Cast<ABTGameSession>(GameSession);
	TempGameSession->OnSessionCreated.AddDynamic(this, &ABTLobbyServerGM::OnEOSSessionCreated);
}

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

void ABTLobbyServerGM::RequestCloudHostIp()
{
	// Get Cloud Host IP
	UVaRestRequestJSON* Request = GetHttpRequestActor()->CreateRequest(EVaRestRequestVerb::GET, EVaRestRequestContentType::x_www_form_urlencoded_url);
	Request->OnRequestComplete.AddDynamic(this, &ABTLobbyServerGM::OnGetCloudHostIpCompleted);
	Request->ProcessURL(UBTGameFunctionLibrary::Ipifp);
}

void ABTLobbyServerGM::OnGetCloudHostIpCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleGetDataCompleted Response: %s"), *ResponseContent);
		BEIp = Request->GetResponseObject()->GetString();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnGetCloudHostIpCompleted: Request failed"));
	}
}

ABTLobbyServerGM::ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer)
{
	GameSessionClass = ABTGameSession::StaticClass();
}

void ABTLobbyServerGM::BeginPlay()
{
	BTLOG_WARNING("[ABTLobbyServerGM] -BeginPlay");

	Super::BeginPlay();
#if WITH_EOS_SESSION
	InitEOS();
#endif	
	InitGameLift();
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

void ABTLobbyServerGM::UpdateEosSessionData(UVaRestJsonObject* Data)
{
	// Get Cloud Host IP
	UVaRestRequestJSON* Request = GetHttpRequestActor()->CreateRequest(EVaRestRequestVerb::POST, EVaRestRequestContentType::json);
	Request->OnRequestComplete.AddDynamic(this, &ABTLobbyServerGM::OnUpdateEosSessionDataCompleted);
	Request->SetHeader(TEXT("x-api-key"), UBTGameFunctionLibrary::XAPIKey);
	Request->GetRequestObject()->MergeJsonObject(Data, true);
	Request->ProcessURL(UBTGameFunctionLibrary::GetUpdateSessionDataURL());
}

void ABTLobbyServerGM::OnUpdateEosSessionDataCompleted(UVaRestRequestJSON* Request)
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

ABTHttpRequest* ABTLobbyServerGM::GetHttpRequestActor()
{
	if (HttpRequestActor)
		return HttpRequestActor;

	HttpRequestActor = Cast<ABTHttpRequest>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), ABTHttpRequest::StaticClass()));
	return HttpRequestActor;
}

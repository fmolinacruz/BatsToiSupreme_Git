// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BTHttpRequest.h"
#include "VaRestSubsystem.h"
#include "VaRestRequestJSON.h"

// Sets default values
ABTHttpRequest::ABTHttpRequest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UVaRestRequestJSON* ABTHttpRequest::CreateRequest(EVaRestRequestVerb Verb, EVaRestRequestContentType ContentType)
{
	UVaRestSubsystem* VaRestSubsystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	if (VaRestSubsystem)
	{
		// Create a new VaRest JSON request
		UVaRestRequestJSON* Request = VaRestSubsystem->ConstructVaRestRequestExt(Verb, ContentType);
		return Request;
	}
	return nullptr;
}

void ABTHttpRequest::GetData(const FString& Url)
{
	// Get the VaRestSubsystem
	UVaRestSubsystem* VaRestSubsystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	if (VaRestSubsystem)
	{
		// Create a new VaRest JSON request
		UVaRestRequestJSON* Request = VaRestSubsystem->ConstructVaRestRequestExt(EVaRestRequestVerb::GET, EVaRestRequestContentType::x_www_form_urlencoded_url);
		// Bind the callback function
		Request->OnRequestComplete.AddDynamic(this, &ABTHttpRequest::HandleGetDataCompleted);
		Request->ProcessURL(Url);
	}
}

void ABTHttpRequest::HandleGetDataCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleGetDataCompleted Response: %s"), *ResponseContent);
		OnGetDataCompleted.Broadcast(Request->GetResponseObject());
		OnGetDataCompleted.Clear();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request failed"));
	}
	
}

void ABTHttpRequest::UpdateSessionData(FString Url, FString ApiKey, UVaRestJsonObject* Data)
{
	// Get the VaRestSubsystem
	UVaRestSubsystem* VaRestSubsystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	if (VaRestSubsystem)
	{
		// Create a new VaRest JSON request
		UVaRestRequestJSON* Request = VaRestSubsystem->ConstructVaRestRequestExt(EVaRestRequestVerb::POST, EVaRestRequestContentType::json);
		// Bind the callback function
		Request->OnRequestComplete.AddDynamic(this, &ABTHttpRequest::HandleUpdateSessionDataCompleted);
		Request->SetHeader(TEXT("x-api-key"), ApiKey);
		Request->GetRequestObject()->MergeJsonObject(Data, true);
		Request->ProcessURL(Url);
	}
}

void ABTHttpRequest::HandleUpdateSessionDataCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleUpdateSessionDataCompleted Response: %s"), *ResponseContent);
		OnUpdateSessionDataCompleted.Broadcast(Request->GetResponseObject());
		OnUpdateSessionDataCompleted.Clear();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request failed"));
	}
}

void ABTHttpRequest::GetSessionData(FString Url, FString SessionId, FString AccountId)
{
	// Get the VaRestSubsystem
	UVaRestSubsystem* VaRestSubsystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	if (VaRestSubsystem)
	{
		// Create a new VaRest JSON request
		UVaRestRequestJSON* Request = VaRestSubsystem->ConstructVaRestRequestExt(EVaRestRequestVerb::GET, EVaRestRequestContentType::x_www_form_urlencoded_url);
		// Bind the callback function
		Request->OnRequestComplete.AddDynamic(this, &ABTHttpRequest::HandleGetSessionDataCompleted);
		Request->SetHeader(TEXT("Authorization"), AccountId);
		Request->GetRequestObject()->SetStringField(TEXT("sessionID"), SessionId);
		Request->ProcessURL(Url);
	}
}

void ABTHttpRequest::HandleGetSessionDataCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleGetSessionDataCompleted Response: %s"), *ResponseContent);
		OnGetSessionDataCompleted.Broadcast(Request->GetResponseObject());
		OnGetSessionDataCompleted.Clear();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request failed"));
	}
}

void ABTHttpRequest::GameLiftSessionCreate(FString Url, FString AccountId)
{
	// Get the VaRestSubsystem
	UVaRestSubsystem* VaRestSubsystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	if (VaRestSubsystem)
	{
		// Create a new VaRest JSON request
		UVaRestRequestJSON* Request = VaRestSubsystem->ConstructVaRestRequestExt(EVaRestRequestVerb::POST, EVaRestRequestContentType::json);
		// Bind the callback function
		Request->OnRequestComplete.AddDynamic(this, &ABTHttpRequest::HandleGameLiftSessionCreateCompleted);
		Request->SetHeader(TEXT("Authorization"), AccountId);
		//Set Latencies , Temp CHEAT
		UVaRestJsonObject* Latencies = NewObject<UVaRestJsonObject>();
		Latencies->SetNumberField(TEXT("ap-northeast-1"), 50);
		Latencies->SetNumberField(TEXT("us-east-1"), 60);
		Request->GetRequestObject()->SetObjectField(TEXT("Latencies"), Latencies);
		Request->ProcessURL(Url);
	}
}

void ABTHttpRequest::HandleGameLiftSessionCreateCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleGameLiftSessionCreateCompleted Response: %s"), *ResponseContent);
		OnGameLiftSessionCreateCompleted.Broadcast(Request->GetResponseObject());
		OnGameLiftSessionCreateCompleted.Clear();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameLiftSessionCreate Failed"));
	}
}

void ABTHttpRequest::GetGameLiftSessionStatus(FString Url, FString TicketId, FString AccountId)
{
	// Get the VaRestSubsystem
	UVaRestSubsystem* VaRestSubsystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	if (VaRestSubsystem)
	{
		// Create a new VaRest JSON request
		UVaRestRequestJSON* Request = VaRestSubsystem->ConstructVaRestRequestExt(EVaRestRequestVerb::GET, EVaRestRequestContentType::x_www_form_urlencoded_url);
		// Bind the callback function
		Request->OnRequestComplete.AddDynamic(this, &ABTHttpRequest::HandleGameLiftGetSessionStatusCompleted);
		Request->SetHeader(TEXT("Authorization"), AccountId);
		Request->GetRequestObject()->SetStringField(TEXT("id"), TicketId);
		Request->ProcessURL(Url);
	}
}

void ABTHttpRequest::HandleGameLiftGetSessionStatusCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleGameLiftGetSessionStatusCompleted Response: %s"), *ResponseContent);
		OnGetGameLiftGetSessionStatusCompleted.Broadcast(Request->GetResponseObject());
		OnGetGameLiftGetSessionStatusCompleted.Clear();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GetGameLiftSessionStatus Failed"));
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/VaRestHttpRequest.h"
#include "VaRestRequestJSON.h"
#include "VaRestSubsystem.h"
#include <Subsystems/SubsystemBlueprintLibrary.h>
#include "Dom/JsonObject.h"

VaRestHttpRequest::VaRestHttpRequest()
{
	HostURL = "https://mnb85lqzo0.execute-api.ap-northeast-1.amazonaws.com/Dev/matchmaking";
}

VaRestHttpRequest::~VaRestHttpRequest()
{
}

void VaRestHttpRequest::MatchMakingCreate()
{
	/*/
	UVaRestSubsystem* Varestsub = GetVARestSub();
	UVaRestRequestJSON* JsonRequest = Varestsub->ConstructVaRestRequestExt(EVaRestRequestVerb::POST, EVaRestRequestContentType::json);
	
	FString HeaderName = "Authorization";
	FString HeaderValue = "AccountID D1";
	JsonRequest->SetHeader(HeaderName, HeaderValue);

	FString FieldName = "Latencies";
	UVaRestJsonObject* JsonObj = JsonRequest->GetRequestObject();
	//UVaRestJsonObject* LatenciesObj = new UVaRestJsonObject();
	//JsonObj->SetNumberField("Ap-northeast", 50);
	//JsonObj->SetObjectField(FieldName, LatenciesObj);
	//JsonRequest->ApplyURL(HostURL)
	*/
}

void VaRestHttpRequest::MatchMakingGetStatus()
{
}


UVaRestSubsystem* VaRestHttpRequest::GetVARestSub()
{
	UVaRestSubsystem* Subsystem{};

	Subsystem = CastChecked<UVaRestSubsystem>(USubsystemBlueprintLibrary::GetEngineSubsystem(UVaRestSubsystem::StaticClass()), ECastCheckedType::NullAllowed);

	if (::IsValid(Subsystem))
	{
		return Subsystem;
	}

	return nullptr;
}

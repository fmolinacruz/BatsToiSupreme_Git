// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <VaRestJsonObject.h>
#include "BTHttpRequest.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetDataEvent, UVaRestJsonObject*, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateSessionDataEvent, UVaRestJsonObject*, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetSessionDataEvent, UVaRestJsonObject*, Result);

UCLASS()
class BATSTOISUPREME_REAL_API ABTHttpRequest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABTHttpRequest();

	// Get Data from URL
	UFUNCTION(BlueprintCallable, Category = "Batstoi|HttpRequest")
	UVaRestRequestJSON* CreateRequest(EVaRestRequestVerb Verb, EVaRestRequestContentType ContentType);

	//Get Data from URL
	UFUNCTION(BlueprintCallable, Category = "Batstoi|HttpRequest")
	void GetData(const FString& Url);

	UFUNCTION()
	void HandleGetDataCompleted(UVaRestRequestJSON* Request);

	UPROPERTY(BlueprintAssignable, Category = "Batstoi|HttpRequest")
	FOnGetDataEvent OnGetDataCompleted;

	//Update Session Data to Server less
	UFUNCTION(BlueprintCallable, Category = "Batstoi|HttpRequest")
	void UpdateSessionData(FString Url, FString ApiKey, UVaRestJsonObject* Data);
	UFUNCTION()
	void HandleUpdateSessionDataCompleted(UVaRestRequestJSON* Request);
	UPROPERTY(BlueprintAssignable, Category = "Batstoi|HttpRequest")
	FUpdateSessionDataEvent OnUpdateSessionDataCompleted;

	//Get Session Data from server less
	UFUNCTION(BlueprintCallable, Category = "Batstoi|HttpRequest")
	void GetSessionData(FString Url, FString SessionId, FString AccountId);
	UFUNCTION()
	void HandleGetSessionDataCompleted(UVaRestRequestJSON* Request);
	UPROPERTY(BlueprintAssignable, Category = "Batstoi|HttpRequest")
	FGetSessionDataEvent OnGetSessionDataCompleted;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BTGameFunctionLibrary.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API UBTGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = BatstoiLibrary)
	static class ABTGameState* GetBTGameState(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = BatstoiLibrary)
	static class ABTGameplayManager* GetBTGameplayManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = BatstoiLibrary)
	static FString GetDeviceId();

	//Get Account id. TODO: EOS account
	UFUNCTION(BlueprintPure, Category = BatstoiLibrary)
	static FString GetAccountId();

	//Get AWS Serverless URL
	UFUNCTION(BlueprintPure, Category = BatstoiLibrary)
	static FString GetServerlessURL();

	//Get AWS Serverless URL for Update Session Data
	UFUNCTION(BlueprintPure, Category = BatstoiLibrary)
	static FString GetUpdateSessionDataURL();

	// Get AWS Serverless URL for Update Session Data
	UFUNCTION(BlueprintPure, Category = BatstoiLibrary)
	static FString GetGetSessionDataURL();

	static const FString ServerlessURL;
	static const FString UpdateSessionDataAPI;
	static const FString GetSessionDataAPI;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/BTGameFunctionLibrary.h"

#include "GameModes/BTGameModeBase.h"
#include "GameModes/BTGameState.h"
#include "Kismet/GameplayStatics.h"

const FString UBTGameFunctionLibrary::ServerlessURL = TEXT("https://mnb85lqzo0.execute-api.ap-northeast-1.amazonaws.com/Dev");
const FString UBTGameFunctionLibrary::UpdateSessionDataAPI = TEXT("/internal/session/data");
const FString UBTGameFunctionLibrary::GetSessionDataAPI = TEXT("/session/data");

ABTGameState* UBTGameFunctionLibrary::GetBTGameState(const UObject* WorldContextObject)
{
	return Cast<ABTGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}

ABTGameplayManager* UBTGameFunctionLibrary::GetBTGameplayManager(const UObject* WorldContextObject)
{
	return Cast<ABTGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject))->GetGameplayManager();
}

FString UBTGameFunctionLibrary::GetDeviceId()
{
	FString DeviceId = FPlatformProcess::ComputerName();
	return DeviceId;
}

FString UBTGameFunctionLibrary::GetAccountId()
{
	FString result = TEXT("AccountID ") + GetDeviceId();
	return result;
}

FString UBTGameFunctionLibrary::GetServerlessURL()
{
	return ServerlessURL;
}

FString UBTGameFunctionLibrary::GetUpdateSessionDataURL()
{
	return ServerlessURL + UpdateSessionDataAPI;
}

FString UBTGameFunctionLibrary::GetGetSessionDataURL()
{
	return ServerlessURL + GetSessionDataAPI;
}

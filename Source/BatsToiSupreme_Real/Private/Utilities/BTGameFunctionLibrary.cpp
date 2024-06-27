// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/BTGameFunctionLibrary.h"

#include "GameModes/BTGameModeBase.h"
#include "GameModes/BTGameState.h"
#include "Kismet/GameplayStatics.h"
#include <SocketSubsystem.h>

const FString UBTGameFunctionLibrary::ServerlessURL = TEXT("https://5ln56m6qu8.execute-api.ap-northeast-1.amazonaws.com/Dev");
const FString UBTGameFunctionLibrary::UpdateSessionDataAPI = TEXT("/internal/session/data");
const FString UBTGameFunctionLibrary::GetSessionDataAPI = TEXT("/session/data");
const FString UBTGameFunctionLibrary::XAPIKey = TEXT("UzpmMSlfazp8UXFrZ0pfTCI9P25Pa3BFQl1RZ0hPVEhSZ3plJ11qZHIwJTp3aktrJkl0JislZVMzbEd2cyNxbEBBJThiXCI0RSlzeVlkeSNvcCc6ZVA+QWwgSSJQclM8");

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

FString UBTGameFunctionLibrary::GetAPIKey()
{
	return XAPIKey;
}

FString UBTGameFunctionLibrary::GetLocalIP()
{
	bool bCanBindAll;
	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll);

	if (Addr->IsValid())
	{
		return Addr->ToString(false);
	}
	else
	{
		return FString(TEXT(""));
	}
}

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
const FString UBTGameFunctionLibrary::CustomConfigPath = FPaths::ProjectConfigDir() / TEXT("CustomConfig.ini");
const FString UBTGameFunctionLibrary::Ipifp = TEXT("http://api.ipify.org");


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
		return FString();
	}
}

FString UBTGameFunctionLibrary::GetPIEHOST()
{
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*CustomConfigPath))
	{
		FString PIELanHost;
		if (GConfig->GetString(TEXT("CustomSection"), TEXT("PIELanHost"), PIELanHost, CustomConfigPath))
		{
			UE_LOG(LogTemp, Log, TEXT("PIELanHost: %s"), *PIELanHost);
			return PIELanHost;
		}
	}
	return FString();
}

bool UBTGameFunctionLibrary::IsLanHost()
{
	FString HostType;
	// Get Lan Host from command line arguments
	if (FParse::Value(FCommandLine::Get(), TEXT("-HOSTTYPE="), HostType))
	{
		if (HostType == "LAN")
		{
			UE_LOG(LogTemp, Warning, TEXT("IsLanHost: LAN"));
			return true;
		}
		if (HostType == "CLOUD")
		{
			UE_LOG(LogTemp, Warning, TEXT("IsLanHost: CLOUD"));
			return false;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("IsLanHost: PIE"));
	return true;
}

bool UBTGameFunctionLibrary::IsUseEOS()
{
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*CustomConfigPath))
	{
		bool isUse;
		if (GConfig->GetBool(TEXT("CustomSection"), TEXT("UseEOS"), isUse, CustomConfigPath))
		{
			return isUse;
		}
	}
	return false;
}

AActor* UBTGameFunctionLibrary::GetOrCreateWorldActor(UWorld* World, UClass* Class)
{
	AActor* Actor = UGameplayStatics::GetActorOfClass(World, Class);
	if (!Actor)
	{
		// Spawn
		FActorSpawnParameters SpawnParams;
		Actor = World->SpawnActor<AActor>(Class, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}
	return Actor;
}

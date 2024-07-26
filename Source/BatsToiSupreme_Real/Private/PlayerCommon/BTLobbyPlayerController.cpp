// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommon/BTLobbyPlayerController.h"
#include "Core.h" 
#include <Utilities/BTLogging.h>
#include "Containers/Array.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include <Utilities/BTGameFunctionLibrary.h>
#include <Utilities/BTHttpRequest.h>
#include <Utilities/EOSUtils.h>

void ABTLobbyPlayerController::BeginPlay()
{
	// On BeginPlay call our login function. This is only on the GameClient, not on the DedicatedServer.

	Super::BeginPlay();
	CppInit();

	//Run on Client
	if (!IsRunningDedicatedServer())
	{
		UE_LOG(LogTemp, Log, TEXT("EOSLogin into EOS..."));
		//Only Login Eos when EOS enable
		if (UBTGameFunctionLibrary::IsUseEOS())
		{
			AEOSUtils* EOS = Cast<AEOSUtils>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), AEOSUtils::StaticClass()));
			if (EOS)
			{
				EOS->Login();
			}
		}
		else //Connect Host direct from host on custom config
		{
			FString BEUrl = UBTGameFunctionLibrary::GetPIEHOST();
			UGameplayStatics::OpenLevel(GetWorld(), *BEUrl);
		}
	}

}

void ABTLobbyPlayerController::CppInit()
{
	
}

FString ABTLobbyPlayerController::GetLanHostUrl()
{
	if (LanHostUrl.IsEmpty())
	{
		// Get Lan Host from command line arguments
		if (FParse::Value(FCommandLine::Get(), TEXT("-LANHOST="), LanHostUrl))
		{
			BTLOG_WARNING("LAN HOST: %s", *LanHostUrl);
		}
		else
		{
			LanHostUrl = UBTGameFunctionLibrary::GetPIEHOST();
			BTLOG_WARNING("GetPIEHOST: %s", *LanHostUrl);
		}
	}

	return LanHostUrl;
}

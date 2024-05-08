// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommon/BTLobbyPlayerController.h"
#include "Core.h" 
#include <Utilities/BTLogging.h>

FString ABTLobbyPlayerController::GetDeviceId()
{
	FString DeviceId = FPlatformProcess::ComputerName(); 
	BTLOG_DISPLAY("[ABTLobbyPlayerController] [GetDeviceId] %s", *DeviceId);
	return DeviceId;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLiftServerSDK.h"

/**
 * 
 */
class BATSTOISUPREME_REAL_API GameLiftUtils : public AActor
{
public:
	GameLiftUtils();
	~GameLiftUtils();

	void Init();
	void InitSDKEC2();
	void InitSDKAnyWhere();

	void StartServerTimeOut();
	void OnServerTimeOut();
	bool HasGameSessionStarted() { return mGameSessionStarted; }

	FGameLiftServerSDKModule* GameLiftSDKModule;
	FServerParameters* GameLiftServerParams;
	FProcessParameters* GameLiftProcessParams;
	int ClientConnectTimeOut = 60; // in Seconds
	bool HasClientConnected = false;
	bool mGameSessionStarted;

private:
	UWorld* World;
};

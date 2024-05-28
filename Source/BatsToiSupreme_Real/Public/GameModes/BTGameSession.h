// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "BTGameSession.generated.h"

/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API ABTGameSession : public AGameSession
{
	GENERATED_BODY()

public: 
	// Function to create an EOS session.
	void CreateSession(FName KeyName = "KeyName", FString KeyValue = "KeyValue");
	void HandleCreateSessionCompleted(FName EOSSessionName, bool bWasSuccessful);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "BTLobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API ABTLobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Function called when play begins.
	virtual void BeginPlay();

	UFUNCTION()
	void CppInit();

public:

	// Function Get Lan Host Url
	UFUNCTION(BlueprintCallable, Category = "Batstoi|LobbyPlayer")
	FString GetLanHostUrl();

private:
	FString LanHostUrl;
};

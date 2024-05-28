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

public:
	UFUNCTION(BlueprintCallable, Category = "Batstoi|Utils")
	FString GetDeviceId();

	// Function to sign into EOS Game Services
	UFUNCTION(BlueprintCallable, Category = "Batstoi|EOS")
	void EOSLogin();

	// Callback function. This function is ran when signing into EOS Game Services completes. 
	void OnEOSLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	// Delegate to bind callback event for login.
	FDelegateHandle LoginDelegateHandle;
};

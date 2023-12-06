// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BTGameModeBase.h"
#include "BTLocalMultiGameMode.generated.h"
#include "Input/InputReceive.h"
#include <Menu/Menu.h>
#include <Characters/BTPlayerCharacter.h>
#include <Camera/BTCamera.h>

/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalMultiGameMode : public ABTGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void GetPlayerStartPoints(AActor* Actor);
	void GetPlayerStartPoints();
	void SpawnInputReceivers();

	UPROPERTY(EditAnywhere, Category = "Camera")
	TSubclassOf<AActor> BP_Camera;

	UPROPERTY(EditAnywhere, Category = "Player Start")
	TSubclassOf<AActor> PlayerStart;

	TArray<AActor*> PlayerStartArray;
	TArray<AInputReceive*> PlayerInputReceiverArray;
	TArray<APlayerController*> PlayerControllerArray;
	UMenu* MenuWidgetRef;
	TArray<ABTPlayerCharacter*> Players;
	int MinPlayers;
	bool bIsInGame;
	ABTCamera CameraRef;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BTGameModeBase.h"
#include "Input/InputReceive.h"
#include <Characters/BTPlayerCharacter.h>
#include <Camera/BTCamera.h>
#include <GameFramework/PlayerStart.h>
#include <Menu/LocalCharacterSelectMenu.h>

#include "BTLocalMultiGameMode.generated.h"
/**
 * 
 */
UCLASS(Blueprintable)
class BATSTOISUPREME_REAL_API ABTLocalMultiGameMode : public ABTGameModeBase
{
	GENERATED_BODY()

public:
	// Called when the game starts
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	virtual void BeginPlay() override;
	
protected:

	void GetPlayerStartPoints();
	void SpawnInputReceivers();
	int NameToInt(AActor* PlayerStart);
	void RemoveUnusedCameras();
	void CreateLocalPlayerDebug(int ControllerId);
	void GameStarted();

	UFUNCTION(BlueprintCallable, Category = "Utilities")
	bool StartGame1();

	//Property
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Template")
	TSubclassOf <ABTCamera> CameraTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Template")
	TSubclassOf <ULocalCharacterSelectMenu> LocalCharacterSelectMenuTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Template")
	TSubclassOf<AGSCModularCharacter> ThirdPersionPlayerAITemplate;


	TArray<AActor*> PlayerStartArray;
	TArray<AInputReceive*> PlayerInputReceiverArray;
	TArray<APlayerController*> PlayerControllerArray;
	TArray<ABTPlayerCharacter*> Players;
	ULocalCharacterSelectMenu* MenuWidgetRef;
	ABTCamera* CameraRef;
	int MinPlayers;
	bool bIsInGame;
	UWorld* World;
};

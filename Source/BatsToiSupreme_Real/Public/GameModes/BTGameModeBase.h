// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLiftServerSDK.h"
#include "GameFramework/GameModeBase.h"
#include "Input/BTInputReceiver.h"
#include "BTGameModeBase.generated.h"

// Forward declarations
class ABTBaseCharacter;

// Player datas
USTRUCT()
struct FPlayerData
{
	GENERATED_BODY()

	int CharacterID;
	ABTPlayerController* Controller;
};

/******************************************************************************
 * Main GameMode API
 ******************************************************************************/
UCLASS()
class BATSTOISUPREME_REAL_API ABTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABTGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnPostLogin(AController* NewPlayer) override;

	void CheckForSpawningPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex);
	void StartSpawningPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex);
	void RestorePlayerCharacter(int PlayerIndex);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<AActor> CameraClass;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<ABTBaseCharacter> CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|Players")
	TArray<ABTBaseCharacter*> PlayerCharacters;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<ABTInputReceiver> InputReceiverClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|Players")
	TArray<ABTInputReceiver*> InputReceivers;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	bool bIsLocal = false;

private: // Default game setup
	void GetMainCameraRef();
	void GetStartSpots();

	UPROPERTY(Transient)
	TObjectPtr<AActor> MainCameraRef;

	UPROPERTY(Transient)
	TArray<AActor*> StartSpots;

	UPROPERTY(Transient)
	int CurrentPlayerIndex = 0;

	UPROPERTY(Transient)
	TMap<int, FPlayerData> PlayerMap;

private: // GameLift
	void InitGameLift();
	void InitSDKEC2();
	void InitSDKAnyWhere();

	void OnGameLiftSessionStart(Aws::GameLift::Server::Model::GameSession ActivatedSession);
	void OnGameLiftSessionUpdate(Aws::GameLift::Server::Model::UpdateGameSession UpdatedSession);
	void OnGameLiftProcessTerminate();
	bool OnGameLiftServerHealthCheck();

	FGameLiftServerSDKModule* GameLiftSDKModule;
	FServerParameters GameLiftServerParams;
	FProcessParameters GameLiftProcessParams;
};

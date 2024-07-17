// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#if WITH_GAMELIFT
#include "GameLiftServerSDK.h"
#endif
#include "GameFramework/GameModeBase.h"
#include "Input/BTInputReceiver.h"
#include "BTGameModeBase.generated.h"

// Forward declarations
class ABTGameplayManager;
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
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	void CheckForSpawningPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex);
	void StartSpawningPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex);
	void RestorePlayerCharacter(int PlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "BatstoiGamemode|Component")
	FORCEINLINE ABTGameplayManager* GetGameplayManager() const
	{
		return GameplayManagerRef;
	}
	
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

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<ABTGameplayManager> GameplayManagerClass;
	
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

	UPROPERTY(Transient)
	TObjectPtr<ABTGameplayManager> GameplayManagerRef;
	
	void InitGameplaySettings();
#if WITH_GAMELIFT
	void InitGameLift();
	void InitSDKEC2();
	void InitSDKAnyWhere();

	void OnGameLiftSessionStart(Aws::GameLift::Server::Model::GameSession ActivatedSession);
	void OnGameLiftSessionUpdate(Aws::GameLift::Server::Model::UpdateGameSession UpdatedSession);
	void OnGameLiftProcessTerminate();
	bool OnGameLiftServerHealthCheck();

	void StartServerTimeOut();
	void OnServerTimeOut();
	bool HasGameSessionStarted() { return mGameSessionStarted; }

	FGameLiftServerSDKModule* GameLiftSDKModule;
	FServerParameters GameLiftServerParams;
	FProcessParameters GameLiftProcessParams;
	int ClientConnectTimeOut = 60;// in Seconds
	bool HasClientConnected = false;
	bool mGameSessionStarted;
#endif
};

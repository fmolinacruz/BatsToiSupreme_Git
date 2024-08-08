// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Input/BTLocalInputReceiver.h"
#include "BTLocalOfflineGameMode.generated.h"


class ABTBaseCharacter;

// Player datas
USTRUCT()
struct FLocalPlayerData
{
	GENERATED_BODY()

	int CharacterID;
	ABTLocalPlayerController* Controller;
};

UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalOfflineGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABTLocalOfflineGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	int NameToInt(AActor* Player);

	void CheckForSpawningPlayerCharacter(ABTLocalPlayerController* PC, int CharacterID, int PlayerIndex);
	void StartSpawningPlayerCharacter(ABTLocalPlayerController* PC, int CharacterID, int PlayerIndex);
	void RestorePlayerCharacter(int PlayerIndex);

public:
	//UPROPERTY(Transient, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UWBTMenu> MenuWidgetRefCPP;

	// MenuWidgetRefCPP
	UPROPERTY(Transient)
	TObjectPtr<UWBTMenu> MenuWidgetRefCPP;

	UWBTMenu* GetMenuWidgetRef() const;

	//UPROPERTY(EditDefaultsOnly, Category = "Batstoi|UI", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UWBTMenu> MenuUIClass;

protected:
	virtual void BeginPlay() override;

	void SpawnInputReceivers();

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<AActor> CameraClass;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<ABTBaseCharacter> CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|Players")
	TArray<ABTBaseCharacter*> PlayerCharacters;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	bool bIsLocal = false;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	bool bIsMenuCreated = false;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<ABTLocalInputReceiver> InputReceiverClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|Players")
	TArray<ABTLocalInputReceiver*> InputReceivers;

private: // Default game setup
	void GetMainCameraRef();
	void GetStartSpots();

	void CreateMenuUI();
	void HideMenuUI();

	UPROPERTY(Transient)
	TObjectPtr<AActor> MainCameraRef;

	UPROPERTY(Transient)
	TArray<AActor*> StartSpots;

	UPROPERTY(Transient)
	int CurrentPlayerIndex = 0;

	UPROPERTY(Transient)
	TMap<int, FLocalPlayerData> PlayerMap;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi|UI")
	TSubclassOf<UWBTMenu> MenuUIClass;
};

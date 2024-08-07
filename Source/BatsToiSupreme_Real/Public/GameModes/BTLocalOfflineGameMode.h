// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Input/BTLocalInputReceiver.h"
#include "BTLocalOfflineGameMode.generated.h"


class ABTBaseCharacter;

UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalOfflineGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABTLocalOfflineGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	int NameToInt(AActor* Player);

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

private: // Default game setup
	void GetMainCameraRef();
	void GetStartSpots();

	UPROPERTY(Transient)
	TObjectPtr<AActor> MainCameraRef;

	UPROPERTY(Transient)
	TArray<AActor*> StartSpots;

	UPROPERTY(Transient)
	int CurrentPlayerIndex = 0;
};

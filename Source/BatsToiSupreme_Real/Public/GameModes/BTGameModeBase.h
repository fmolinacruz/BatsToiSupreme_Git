// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Input/BTInputReceiver.h"
#include "BTGameModeBase.generated.h"

class ABTBaseCharacter;

UCLASS()
class BATSTOISUPREME_REAL_API ABTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABTGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnPostLogin(AController* NewPlayer) override;

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
	bool bIsLocal = false;


private:
	void GetMainCameraRef();
	void GetStartSpots();

	UPROPERTY(Transient)
	TObjectPtr<AActor> MainCameraRef;

	UPROPERTY(Transient)
	TArray<AActor*> StartSpots;

	int CurrentPlayerIndex = 0;

//public:
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Batstoi")
//	bool bUseInputReceiver = false;

public:
	void SpawnPlayerCharacter(ABTPlayerController* PC, int CharacterID, int PlayerIndex);
};

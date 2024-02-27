// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Input/InputReceive.h"
#include "Camera/BTCamera.h"
#include "BTLocalBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABTLocalBaseGameMode();

	// Called when the game starts
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	virtual void BeginPlay() override;

protected:
	//void GetPlayerStartPoints();
	void FindMainCameraRef();
	void SpawnInputReceivers();
	//int NameToInt(AActor* PlayerStart);

protected:
	TArray<AActor*> PlayerStartArray;
	UWorld* World;
	TArray<AInputReceive*> PlayerInputReceiverArray;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Template")
	//TSubclassOf<ABTCamera> CameraTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<ABTBaseCharacter> CharacterClass;

	ABTCamera* CameraRef;
	TArray<ABTBaseCharacter*> PlayerCharacters;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TSubclassOf<AActor> MainCameraClass;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<AActor> MainCameraRef;
};

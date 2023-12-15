// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTGameModeBase.generated.h"

class ABTBaseCharacter;

UCLASS()
class BATSTOISUPREME_REAL_API ABTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABTGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<AActor> CameraClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Batstoi")
	TSubclassOf<ABTBaseCharacter> CharacterClass;

private:
	void GetMainCameraRef();
	void GetStartSpots();
	
	UPROPERTY(Transient)
	TObjectPtr<AActor> MainCameraRef;
	
	UPROPERTY(Transient)
	TArray<AActor*> StartSpots;

	int CurrentPlayerIndex = 0;
};

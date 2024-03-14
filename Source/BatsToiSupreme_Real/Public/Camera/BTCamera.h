// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Characters/BTPlayerCharacter.h>
#include "BTCamera.generated.h"

UCLASS(Blueprintable)
class BATSTOISUPREME_REAL_API ABTCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABTCamera();

	//Game Started
	void GameStarted(TArray<ABTPlayerCharacter*> ActivePlayers);

	//Event Print Counter UI Widget Component
	UFUNCTION(BlueprintNativeEvent, Category = "BTCamera|CounterUI")
	void PrintCounterUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

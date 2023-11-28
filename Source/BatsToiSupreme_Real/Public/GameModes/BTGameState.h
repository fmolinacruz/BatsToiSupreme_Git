// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BTGameState.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API ABTGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ABTGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category="Batstoi")
	float GetServerFPS() const { return ServerFPS; }

protected:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(Replicated)
	float ServerFPS;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTLobbyServerGM.generated.h"

/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API ABTLobbyServerGM : public AGameModeBase
{
	GENERATED_BODY()
protected:
	ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	int32 GetPlayerCount() const;
};

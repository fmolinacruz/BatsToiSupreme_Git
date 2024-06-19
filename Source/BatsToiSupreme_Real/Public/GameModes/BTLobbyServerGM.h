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
private:
	//Get BE Port
	int GetBEPort() const;

	UFUNCTION()
	void OnEOSSessionCreated();

protected:
	ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

	//BE Port
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|LobbyServer")
	int BEPort;

	//BE IP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|LobbyServer")
	FString BEIp;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	int32 GetPlayerCount() const;
};

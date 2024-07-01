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
	void OnEOSSessionCreated(FString sessionId);

	UFUNCTION()
	void Init();

protected:
	ABTLobbyServerGM(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

	//BE Port
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Batstoi|LobbyServer")
	FString BEPort;

	//BE IP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|LobbyServer")
	FString BEIp;

	//EOS session ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Batstoi|LobbyServer")
	FString EosSessionId;

	// Account Id for serverless api
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Batstoi|LobbyServer")
	FString AccountId;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	int32 GetPlayerCount() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Batstoi|LobbyServer")
	void UpdateEosSessionData(UVaRestJsonObject* Data);
};

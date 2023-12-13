// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BTGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	MainMenu,
	InGame,
	PauseMenu
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, const EGameState&, NewState);

UCLASS()
class BATSTOISUPREME_REAL_API ABTGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ABTGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable, Category="Batstoi")
	void ChangeGameState(EGameState NewState);

	UFUNCTION(BlueprintCallable, Category="Batstoi")
	FORCEINLINE float GetServerFPS() const
	{
		return ServerFPS;
	}
	
	UFUNCTION(BlueprintCallable, Category="Batstoi")
	FORCEINLINE EGameState GetGameState() const
	{
		return GameState;
	}

	UPROPERTY(BlueprintAssignable, Category = "Batstoi")
	FOnGameStateChanged OnGameStateChanged;

	void InitializePlayer();

protected:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(Replicated)
	float ServerFPS;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi")
	EGameState GameState = EGameState::MainMenu;
};

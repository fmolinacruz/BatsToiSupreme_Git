// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTGameplayManager.generated.h"

class ABTBaseCharacter;

UCLASS()
class BATSTOISUPREME_REAL_API ABTGameplayManager : public AActor
{
	GENERATED_BODY()

public:
	ABTGameplayManager();

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "BatstoiGameplay")
	TObjectPtr<ABTBaseCharacter> Player01;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "BatstoiGameplay")
	TObjectPtr<ABTBaseCharacter> Player02;

	UFUNCTION(BlueprintCallable, Category = "BatstoiGameplay|Fight")
	void RequestHandFighting(ABTBaseCharacter* BaseCharacter);
	
protected:
	virtual void BeginPlay() override;

private:
	bool IsProcessHandFight;
};

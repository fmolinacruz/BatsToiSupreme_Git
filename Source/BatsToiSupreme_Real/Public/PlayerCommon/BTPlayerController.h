// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BTPlayerController.generated.h"

class ABTPlayerCharacter;

UCLASS()
class BATSTOISUPREME_REAL_API ABTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABTPlayerController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	TObjectPtr<ABTPlayerCharacter> PlayerCharacter;
};

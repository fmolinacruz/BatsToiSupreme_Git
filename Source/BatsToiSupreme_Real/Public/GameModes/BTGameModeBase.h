// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTGameModeBase.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API ABTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABTGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

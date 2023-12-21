// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/BTGameFunctionLibrary.h"

#include "GameModes/BTGameState.h"
#include "Kismet/GameplayStatics.h"

ABTGameState* UBTGameFunctionLibrary::GetBTGameState(const UObject* WorldContextObject)
{
	return Cast<ABTGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}

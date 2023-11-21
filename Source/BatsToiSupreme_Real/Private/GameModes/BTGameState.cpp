// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BTGameState.h"

extern ENGINE_API float GAverageFPS;

ABTGameState::ABTGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABTGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetLocalRole() == ROLE_Authority)
	{
		ServerFPS = GAverageFPS;
	}
}

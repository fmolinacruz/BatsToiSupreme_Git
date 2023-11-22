// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BTGameState.h"

#include "Net/UnrealNetwork.h"

extern ENGINE_API float GAverageFPS;

ABTGameState::ABTGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	ServerFPS = 0.0f;
}

void ABTGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// The replicated property shouldn't be changed on the Client side, so we add this check to
	// make sure we had the authority to change it.
	if (GetLocalRole() == ROLE_Authority)
	{
		ServerFPS = GAverageFPS;
	}
}

// NOTE(Nghia Lam): This function is required whenever we have a property that needs replication.
// In this case that property is ServerFPS.
void ABTGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ServerFPS);
}

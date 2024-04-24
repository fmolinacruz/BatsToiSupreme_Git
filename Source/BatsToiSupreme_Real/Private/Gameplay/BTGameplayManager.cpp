// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/BTGameplayManager.h"

#include "Net/UnrealNetwork.h"


ABTGameplayManager::ABTGameplayManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	IsProcessHandFight = false;
}

void ABTGameplayManager::BeginPlay()
{
	Super::BeginPlay();
}

void ABTGameplayManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABTGameplayManager, Player01);
	DOREPLIFETIME(ABTGameplayManager, Player02);
}

void ABTGameplayManager::RequestHandFighting(ABTBaseCharacter* BaseCharacter)
{
	if (IsProcessHandFight)
		return;

	IsProcessHandFight = true;

	// TODO: Reset IsProcessHandFight after finish
}

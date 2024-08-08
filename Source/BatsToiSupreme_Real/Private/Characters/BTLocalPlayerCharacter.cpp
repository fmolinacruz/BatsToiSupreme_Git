// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTLocalPlayerCharacter.h"

#include "PlayerCommon/BTLocalPlayerInput.h"

ABTLocalPlayerCharacter::ABTLocalPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	BTLocalInputComponent = CreateDefaultSubobject<UBTLocalPlayerInput>(TEXT("Player Input"));
}

void ABTLocalPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

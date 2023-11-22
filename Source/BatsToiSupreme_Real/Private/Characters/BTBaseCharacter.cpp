// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BTBaseCharacter.h"

ABTBaseCharacter::ABTBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABTBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTPlayerCharacter.h"

#include "PlayerCommon/BTPlayerInput.h"

ABTPlayerCharacter::ABTPlayerCharacter()
{
	BTInputComponent = CreateDefaultSubobject<UBTPlayerInput>(TEXT("Player Input"));
}

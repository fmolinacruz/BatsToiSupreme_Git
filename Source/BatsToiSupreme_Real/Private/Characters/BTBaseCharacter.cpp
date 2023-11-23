// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTBaseCharacter.h"

#include "Characters/BTCharacterMovement.h"

ABTBaseCharacter::ABTBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBTCharacterMovement>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	BTMovementComponent = CastChecked<UBTCharacterMovement>(GetMovementComponent());
}

void ABTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

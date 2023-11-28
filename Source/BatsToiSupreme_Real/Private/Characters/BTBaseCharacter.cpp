// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTBaseCharacter.h"

#include "Utilities/BTLogging.h"

ABTBaseCharacter::ABTBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABTBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RotateTowardEnemy(DeltaSeconds);
}

void ABTBaseCharacter::MoveCharacter(const FVector2D& MovementVector)
{
	// Quick movement code.
	// TODO: Revise this code
	BTLOG_WARNING("Movement here: %s !!", *MovementVector.ToString());
	// AddMovementInput(FRotationMatrix(FRotator::ZeroRotator).GetUnitAxis(EAxis::X), MovementVector.X);
	// AddMovementInput(FRotationMatrix(FRotator::ZeroRotator).GetUnitAxis(EAxis::Y), -MovementVector.Y);
}

void ABTBaseCharacter::RotateTowardEnemy(float DeltaSeconds)
{
	if (BTEnemy == nullptr)
	{
		BTLOG_WARNING("BTEnemy is not set correctly !!");
		return;
	}

	const FVector StartLocation = GetActorLocation();
	const FVector TargetLocation = BTEnemy->GetActorLocation();

	const FRotator TargetRotation = FRotationMatrix::MakeFromX(TargetLocation - StartLocation).Rotator();
	const FQuat TargetQuatRotation = FQuat(TargetRotation);
	AddActorLocalRotation(TargetQuatRotation);

	const bool IsStandingStillSelf = GetVelocity().Size() == 0;
	const bool IsStandingStillEnemy = BTEnemy->GetVelocity().Size() == 0;

	if (IsStandingStillSelf == true && IsStandingStillEnemy == false)
	{
		const FVector DirectionToEnemy = BTEnemy->GetActorLocation() - GetActorLocation();
		const FVector VelocityOfEnemy = BTEnemy->GetVelocity();
		const FVector CrossProduct = FVector::CrossProduct(DirectionToEnemy, VelocityOfEnemy);

		bIsTurningRight = CrossProduct.Z > 0;
		bIsTurningLeft = CrossProduct.Z < 0;
	}
	else
	{
		bIsTurningRight = false;
		bIsTurningLeft = false;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTBaseCharacter.h"

#include "Kismet/KismetMathLibrary.h"
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

void ABTBaseCharacter::AddMovementBuffer(const FVector2D& MovementVector)
{
	MovementBufferX = MovementVector.X;
	MovementBufferY = MovementVector.Y;
}

void ABTBaseCharacter::RefreshMovementBuffer()
{
	MovementBufferX = 0;
	MovementBufferY = 0;
}

const FVector ABTBaseCharacter::GetMovementVelocity()
{
	const FRotator GameViewRotator(0, 0, GetControlRotation().Yaw);
	const FVector ForwardVector = MovementBufferY * UKismetMathLibrary::GetForwardVector(GameViewRotator);
	const FVector RightVector = MovementBufferX * UKismetMathLibrary::GetRightVector(GameViewRotator);
	
	FVector CombineVector = ForwardVector + RightVector;
	CombineVector.Normalize(0.001);
	return CombineVector;
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

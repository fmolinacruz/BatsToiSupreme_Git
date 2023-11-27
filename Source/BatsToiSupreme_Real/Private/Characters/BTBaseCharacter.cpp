// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTBaseCharacter.h"

#include "Characters/BTCharacterMovement.h"
#include "Utilities/BTLogging.h"

ABTBaseCharacter::ABTBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBTCharacterMovement>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	BTMovementComponent = CastChecked<UBTCharacterMovement>(GetMovementComponent());
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
	BTLOG_WARNING("Movement here !!");
	AddMovementInput(FRotationMatrix(FRotator::ZeroRotator).GetUnitAxis(EAxis::X), MovementVector.X);
	AddMovementInput(FRotationMatrix(FRotator::ZeroRotator).GetUnitAxis(EAxis::Y), -MovementVector.Y);
}

void ABTBaseCharacter::RotateTowardEnemy(float DeltaSeconds)
{
	if (BTEnemy == nullptr)
		return;

	const FVector StartLocation = GetActorLocation();
	const FVector TargetLocation = BTEnemy->GetActorLocation();

	const FRotator TargetRotation = FRotationMatrix::MakeFromX(TargetLocation - StartLocation).Rotator();
	const FRotator CurrentRotation = GetActorRotation();
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 15.f);
	SetActorRotation(NewRotation);

	const bool IsStandingStillSelf = GetVelocity().Size() == 0;
	const bool IsStandingStillEnemy = BTEnemy->GetVelocity().Size() == 0;

	if (IsStandingStillSelf == true && IsStandingStillEnemy == false)
	{
		const FVector DirectionToPlayer2 = BTEnemy->GetActorLocation() - GetActorLocation();
		const FVector VelocityOfPlayer2 = BTEnemy->GetVelocity();
		const FVector CrossProduct = FVector::CrossProduct(DirectionToPlayer2, VelocityOfPlayer2);

		bIsTurningRight = CrossProduct.Z > 0;
		bIsTurningLeft = CrossProduct.Z < 0;
	}
	else
	{
		bIsTurningRight = false;
		bIsTurningLeft = false;
	}
}

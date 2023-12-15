// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Utilities/BTLogging.h"

ABTBaseCharacter::ABTBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MovementVelocity(FVector::Zero())
{
	PrimaryActorTick.bCanEverTick = true;

	// Basic setup
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
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

void ABTBaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABTBaseCharacter, MovementVelocity);
}

void ABTBaseCharacter::AddMovementBuffer(const FVector2D& MovementVector)
{
	Server_AddMovementBuffer(MovementVector);
}

void ABTBaseCharacter::Server_AddMovementBuffer_Implementation(const FVector2D& MovementVector)
{
	const FRotator GameViewRotator(0, 0, GetControlRotation().Yaw);
	const FVector ForwardVector = MovementVector.Y * UKismetMathLibrary::GetForwardVector(GameViewRotator);
	const FVector RightVector = MovementVector.X * UKismetMathLibrary::GetRightVector(GameViewRotator);

	MovementVelocity = ForwardVector + RightVector;
	MovementVelocity.Normalize(0.001);
}

bool ABTBaseCharacter::Server_AddMovementBuffer_Validate(const FVector2D& MovementVector)
{
	// Add validation of the input here if necessary
	return true;
}

void ABTBaseCharacter::RefreshMovementBuffer()
{
	Server_RefreshMovementBuffer();
}

void ABTBaseCharacter::Server_RefreshMovementBuffer_Implementation()
{
	MovementVelocity = FVector::Zero();
}

bool ABTBaseCharacter::Server_RefreshMovementBuffer_Validate()
{
	// Add validation of the input here if necessary
	return true;
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
	
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);
	const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaSeconds, AutoTurningRate);
	SetActorRotation(NewRotation);

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

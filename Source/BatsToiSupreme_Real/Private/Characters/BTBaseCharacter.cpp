// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Utilities/BTLogging.h"

ABTBaseCharacter::ABTBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Basic setup
	bUseControllerRotationYaw = false; // Disable controller rotation
	bReplicates = true;                // Enable replication for this actor
	SetReplicateMovement(true);        // Enable replication of movement
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpeedX_C = 0.0f;
	SpeedY_C = 0.0f;
}

void ABTBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABTBaseCharacter, BTEnemy);
	//DOREPLIFETIME(ABTBaseCharacter, MovementVelocity);
	DOREPLIFETIME(ABTBaseCharacter, bIsTurningRight);
	DOREPLIFETIME(ABTBaseCharacter, bIsTurningLeft);
	DOREPLIFETIME(ABTBaseCharacter, SpeedX_C);
	DOREPLIFETIME(ABTBaseCharacter, SpeedY_C);
}

void ABTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABTBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Only run rotation logic on the owning client and the server
	if (IsLocallyControlled() || HasAuthority())
	{
		RotateTowardEnemy(DeltaSeconds);
	}
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

	FVector MovementVelocity = ForwardVector + RightVector;
	MovementVelocity.Normalize(0.001);

	float DotProductForward = FVector::DotProduct(MovementVelocity, GetActorForwardVector());
	float DotProductRight = FVector::DotProduct(MovementVelocity, GetActorRightVector());

	float SpeedX_New = DotProductForward * 100.0f;
	float SpeedY_New = DotProductRight * 100.0f;

	SpeedX_C = FMath::Lerp(SpeedX_C, SpeedX_New, 0.3f);
	SpeedY_C = FMath::Lerp(SpeedY_C, SpeedY_New, 0.3f);

//	//if (GEngine)
//	//{
//	//	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("SpeedX_C: %f"), SpeedX_C));
//	//	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("SpeedY_C: %f"), SpeedY_C));
//	//}
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
	//MovementVelocity = FVector::Zero();
	SpeedX_C = 0.0f;
	SpeedY_C = 0.0f;
}

bool ABTBaseCharacter::Server_RefreshMovementBuffer_Validate()
{
	// Add validation of the input here if necessary
	return true;
}

void ABTBaseCharacter::RotateTowardEnemy(float DeltaSeconds)
{
	Internal_RotateTowardEnemy(this, DeltaSeconds);
	if (IsLocallyControlled() && !HasAuthority())
	{
		Server_RotateTowardEnemy(this, DeltaSeconds);
	}
}

void ABTBaseCharacter::Server_RotateTowardEnemy_Implementation(ABTBaseCharacter* InCharacter, float DeltaSeconds)
{
	Internal_RotateTowardEnemy(InCharacter, DeltaSeconds);
}

bool ABTBaseCharacter::Server_RotateTowardEnemy_Validate(ABTBaseCharacter* InCharacter, float DeltaSeconds)
{
	return true;
}

void ABTBaseCharacter::Internal_RotateTowardEnemy(ABTBaseCharacter* InCharacter, float DeltaSeconds)
{
	if (InCharacter->BTEnemy == nullptr)
	{
		BTLOG_WARNING("BTEnemy is not set correctly !!");
		return;
	}

	const FVector StartLocation = InCharacter->GetActorLocation();
	const FVector TargetLocation = InCharacter->BTEnemy->GetActorLocation();

	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);
	const FRotator NewRotation = FMath::RInterpTo(InCharacter->GetActorRotation(), TargetRotation, DeltaSeconds, 100.0f);
	InCharacter->SetActorRotation(NewRotation);

	const bool IsStandingStillSelf = InCharacter->GetVelocity().Size() == 0;
	const bool IsStandingStillEnemy = InCharacter->BTEnemy->GetVelocity().Size() == 0;

	if (IsStandingStillSelf == true && IsStandingStillEnemy == false)
	{
		const FVector DirectionToEnemy = InCharacter->BTEnemy->GetActorLocation() - InCharacter->GetActorLocation();
		const FVector VelocityOfEnemy = InCharacter->BTEnemy->GetVelocity();
		const FVector CrossProduct = FVector::CrossProduct(DirectionToEnemy, VelocityOfEnemy);

		InCharacter->bIsTurningRight = CrossProduct.Z > 0;
		InCharacter->bIsTurningLeft = CrossProduct.Z < 0;
	}
	else
	{
		InCharacter->bIsTurningRight = false;
		InCharacter->bIsTurningLeft = false;
	}
}

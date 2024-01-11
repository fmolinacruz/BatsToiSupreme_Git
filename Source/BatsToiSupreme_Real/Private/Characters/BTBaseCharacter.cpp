// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTBaseCharacter.h"

#include "MotionWarpingComponent.h"
#include "Animation/BTAnimationComponent.h"
#include "Characters/BTCharacterAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Utilities/BTLogging.h"

ABTBaseCharacter::ABTBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MovementBufferX(0.0f), MovementBufferY(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	// Basic setup
	bUseControllerRotationYaw = false; // Disable controller rotation
	bReplicates = true;                // Enable replication for this actor
	SetReplicateMovement(true);        // Enable replication of movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->SetMovementMode(MOVE_Custom);

	// Components
	BTAbilityHandler = CreateDefaultSubobject<UBTCharacterAbilityHandler>(TEXT("Ability Handler"));
	BTAnimationHandler = CreateDefaultSubobject<UBTAnimationComponent>(TEXT("Animation Handler"));
	BTMotionWarp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("Motion Warping"));
}

void ABTBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABTBaseCharacter, BTEnemy);
	DOREPLIFETIME(ABTBaseCharacter, bIsTurningRight);
	DOREPLIFETIME(ABTBaseCharacter, bIsTurningLeft);
	DOREPLIFETIME(ABTBaseCharacter, MovementBufferX);
	DOREPLIFETIME(ABTBaseCharacter, MovementBufferY);
	DOREPLIFETIME(ABTBaseCharacter, PlayerIndex);
	DOREPLIFETIME(ABTBaseCharacter, StaminaAttribute);
}

void ABTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->SetRootMotionMode(ERootMotionMode::IgnoreRootMotion);
		}
	}

}

void ABTBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Only run rotation logic on the owning client and the server
	if (IsLocallyControlled() || HasAuthority())
	{
		RotateTowardEnemy(DeltaSeconds);
	}
	//StaminaAttribute = GetStaminaProgress();
}

float ABTBaseCharacter::GetStaminaProgress() const
{
	if (AbilitySystemComponent)
	{
		return GetAbilitySystemComponent()->GetNumericAttribute(UBTCharacterAttributeSet::GetStaminaAttribute());
	}
	return 0.0f;
}

void ABTBaseCharacter::SetStaminaProgress(float value)
{
	GetAbilitySystemComponent()->SetNumericAttributeBase(UBTCharacterAttributeSet::GetStaminaAttribute(), value);
}

void ABTBaseCharacter::SetStaminaConsumption(float value)
{
	StaminaAttribute = GetStaminaProgress();
	StaminaAttribute -= value;
	StaminaAttribute = fmax(0, StaminaAttribute);
	SetStaminaProgress(StaminaAttribute);

}

void ABTBaseCharacter::AddMovementBuffer(const FVector2D& MovementVector)
{
	if (IsLocallyControlled() || HasAuthority())
	{
		Server_AddMovementBuffer(this, MovementVector);
	}
}

void ABTBaseCharacter::Server_AddMovementBuffer_Implementation(ABTBaseCharacter* InCharacter, const FVector2D& MovementVector)
{
	// TODO: This seems complicated, can we simplify this.
	const FRotator GameViewRotator(0, 0, InCharacter->GetControlRotation().Yaw);
	const FVector ForwardVector = MovementVector.Y * UKismetMathLibrary::GetForwardVector(GameViewRotator);
	const FVector RightVector = MovementVector.X * UKismetMathLibrary::GetRightVector(GameViewRotator);

	FVector MovementVelocity = ForwardVector + RightVector;
	MovementVelocity.Normalize(0.001);

	const float DotProductForward = FVector::DotProduct(MovementVelocity, InCharacter->GetActorForwardVector());
	const float DotProductRight = FVector::DotProduct(MovementVelocity, InCharacter->GetActorRightVector());

	InCharacter->MovementBufferX = FMath::Lerp(MovementBufferX, DotProductForward * 100.0f, 0.3f);
	InCharacter->MovementBufferY = FMath::Lerp(MovementBufferY, DotProductRight * 100.0f, 0.3f);
}

void ABTBaseCharacter::RefreshMovementBuffer()
{
	if (IsLocallyControlled() || HasAuthority())
	{
		Server_RefreshMovementBuffer(this);
	}
}

void ABTBaseCharacter::SetCanAdjustRotation(const bool NewCanAdjust)
{
	bCanAdjustRotation = NewCanAdjust;
}

void ABTBaseCharacter::Server_RefreshMovementBuffer_Implementation(ABTBaseCharacter* InCharacter)
{
	InCharacter->MovementBufferX = 0.0f;
	InCharacter->MovementBufferY = 0.0f;
}

void ABTBaseCharacter::RotateTowardEnemy(float DeltaSeconds)
{
	if (!bCanAdjustRotation)
	{
		return;
	}
	
	Internal_RotateTowardEnemy(this, DeltaSeconds);
	if (IsLocallyControlled() && !HasAuthority())
	{
		Server_RotateTowardEnemy(this, DeltaSeconds);
	}
}

void ABTBaseCharacter::HandleTriggerAbilityInput(const EAbilityInputType InputType)
{
	if (IsLocallyControlled() || HasAuthority())
	{
		BTAbilityHandler->ActivateAbilityWithInput(InputType);
	}
}

void ABTBaseCharacter::HandleTriggerAbilityTag(const FGameplayTag AbilityTag, const ERelativeDirection Direction)
{
	if (IsLocallyControlled() || HasAuthority())
	{
		BTAbilityHandler->ActivateAbilityWithTag(AbilityTag, Direction);
	}
}

void ABTBaseCharacter::SetPlayerIndex(int32 NewIndex)
{
	PlayerIndex = NewIndex;
}

void ABTBaseCharacter::Server_RotateTowardEnemy_Implementation(ABTBaseCharacter* InCharacter, float DeltaSeconds)
{
	Internal_RotateTowardEnemy(InCharacter, DeltaSeconds);
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

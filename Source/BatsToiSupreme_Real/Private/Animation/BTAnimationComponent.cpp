// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/BTAnimationComponent.h"

#include "MotionWarpingComponent.h"
#include "RootMotionModifier.h"
#include "RootMotionModifier_SkewWarp.h"
#include "Characters/BTBaseCharacter.h"
#include "Characters/BTCharacterAttachmentRef.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Utilities/BTLogging.h"

UBTAnimationComponent::UBTAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UBTAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<ABTBaseCharacter>(GetOwner());
	if (!CharacterOwner)
	{
		BTLOG_ERROR("Please ONLY assign this component to ABTBaseCharacter !");
	}
}

void UBTAnimationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Requirements for replicated properties
	DOREPLIFETIME(UBTAnimationComponent, bIsPlayingCombinedAnim);
	DOREPLIFETIME(UBTAnimationComponent, CurrentAnim);
}

bool UBTAnimationComponent::TryPlayCombinedAnimation(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag, const ERelativeDirection& Direction)
{
	if (!CanPlayCombinedAnimWithCharacter(OtherCharacter, CombineAnimTag))
	{
		return false;
	}

	PlayCombinedAnimation(OtherCharacter, CombineAnimTag, Direction);
	return true;
}

void UBTAnimationComponent::PlayCombinedAnimation_Implementation(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag, const ERelativeDirection& Direction)
{
	const FCombinedAnimsData* AnimsData = GetCombinedAnimData(CombineAnimTag, Direction);
	if (AnimsData && AnimsData->AttackerAnimMontage)
	{
		// TODO: Polish code here
		CurrentAnim = FCombinedAnim(*AnimsData, CombineAnimTag, OtherCharacter);

		// Motion Warp
		if (CurrentAnim.AnimData.ReceiverForcePosition == ERelativePosition::SyncBone && CharacterOwner->GetMotionWarp())
		{
			SetAnimationTransformReference(CharacterOwner->BTEnemy);
			
			const FTransform TargetTransform = CharacterOwner->BTEnemy->GetAnimTransformRef()->GetComponentTransform();
			const FMotionWarpingTarget NewTarget = FMotionWarpingTarget(CurrentAnim.AnimData.WarpSyncPoint, TargetTransform);
			
			UMotionWarpingComponent* MotionComp = CharacterOwner->GetMotionWarp();
			MotionComp->AddOrUpdateWarpTarget(NewTarget);

			URootMotionModifier_SkewWarp::AddRootMotionModifierSkewWarp(
				MotionComp,
				CurrentAnim.AnimData.AttackerAnimMontage,
				0.0f, CurrentAnim.AnimData.WarpDuration,
				CurrentAnim.AnimData.WarpSyncPoint,
				EWarpPointAnimProvider::None,
				TargetTransform,
				NAME_None,
				true, true, true,
				EMotionWarpRotationType::Facing,
				CurrentAnim.AnimData.WarpRotationMultiplier
			);
		}

		StartAnimOnAttacker();
		StartAnimOnReceiver();
		bIsPlayingCombinedAnim = true;
	}
}

bool UBTAnimationComponent::PlayCombinedAnimation_Validate(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag, const ERelativeDirection& Direction)
{
	return true;
}

bool UBTAnimationComponent::CanPlayCombinedAnimWithCharacter(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
	return true;
}

bool UBTAnimationComponent::EvaluateCombinedAnim(const FCombinedAnimsData& AnimConfig, const ACharacter* OtherChar) const
{
	return false;
}

void UBTAnimationComponent::OnCombinedAnimStarted(const FGameplayTag& AnimTag) {}

void UBTAnimationComponent::OnCombinedAnimEnded(const FGameplayTag& AnimTag) {}

void UBTAnimationComponent::DispatchAnimStart_Implementation(const FGameplayTag& AnimTag)
{
	OnCombinedAnimationStarted.Broadcast(AnimTag);
	OnCombinedAnimStarted(AnimTag);
}

bool UBTAnimationComponent::DispatchAnimStart_Validate(const FGameplayTag& AnimTag)
{
	return true;
}

void UBTAnimationComponent::DispatchAnimEnded_Implementation(const FGameplayTag& AnimTag)
{
	OnCombinedAnimationEnded.Broadcast(AnimTag);
	OnCombinedAnimEnded(AnimTag);
}

bool UBTAnimationComponent::DispatchAnimEnded_Validate(const FGameplayTag& animTag)
{
	return true;
}

void UBTAnimationComponent::MulticastPlayAnimMontage_Implementation(UAnimMontage* AnimMontage, ACharacter* Character)
{
	if (!Character)
	{
		return;
	}

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->SetRootMotionMode(ERootMotionMode::RootMotionFromEverything);
		Character->PlayAnimMontage(AnimMontage);
	}
}

bool UBTAnimationComponent::MulticastPlayAnimMontage_Validate(UAnimMontage* AnimMontage, ACharacter* Character)
{
	return true;
}

void UBTAnimationComponent::HandleMontageFinished(UAnimMontage* InMontage, bool bIsInterrupted)
{
	if (CurrentAnim.AnimData.AttackerAnimMontage == InMontage)
	{
		DispatchAnimEnded(CurrentAnim.AnimTag);

		UAnimInstance* AnimInstance = (CharacterOwner->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->OnMontageBlendingOut.RemoveDynamic(this, &UBTAnimationComponent::HandleMontageFinished);
		}
		bIsPlayingCombinedAnim = false;
	}
}

void UBTAnimationComponent::SetAnimationTransformReference_Implementation(ABTBaseCharacter* InCharacter)
{
	BTLOG_WARNING("Current Receiver Sync Position: %s", *CurrentAnim.AnimData.ReceiverSyncPosition.ToString());
	InCharacter->GetAnimTransformRef()->SetRelativeTransform(CurrentAnim.AnimData.ReceiverSyncPosition);
}

FCombinedAnimsData* UBTAnimationComponent::GetCombinedAnimData(const FGameplayTag& AnimTag, const ERelativeDirection Direction) const
{
	const auto Anims = AnimsConfigDatabase->GetRowMap();
	for (const auto Anim : Anims)
	{
		FCombinedAnimsData* CurrentData = reinterpret_cast<FCombinedAnimsData*>(Anim.Value);
		if (CurrentData->AnimTag == AnimTag && CurrentData->AnimDirection == Direction)
		{
			return CurrentData;
		}
	}
	return nullptr;
}

void UBTAnimationComponent::StartAnimOnAttacker()
{
	UAnimInstance* AnimInstance = CharacterOwner->GetMesh()->GetAnimInstance();
	if (AnimInstance && CurrentAnim.AnimData.AttackerAnimMontage)
	{
		AnimInstance->OnMontageBlendingOut.AddDynamic(this, &UBTAnimationComponent::HandleMontageFinished);
		MulticastPlayAnimMontage(CurrentAnim.AnimData.AttackerAnimMontage, CharacterOwner);
		DispatchAnimStart(CurrentAnim.AnimTag);
	}
}

void UBTAnimationComponent::StartAnimOnReceiver()
{
	if (!CurrentAnim.ReceiverCharacterRef)
	{
		return;
	}
	
	const UBTAnimationComponent* ReceiverAnimComponent = CurrentAnim.ReceiverCharacterRef->FindComponentByClass<UBTAnimationComponent>();
	if (!ReceiverAnimComponent)
	{
		BTLOG_ERROR("This ReceiverCharacter wasn't setup with a UBTAnimationComponent correctly!");
		return;
	}

	if (CurrentAnim.AnimData.ReceiverAnimMontage)
	{
		MulticastPlayAnimMontage(CurrentAnim.AnimData.ReceiverAnimMontage, CurrentAnim.ReceiverCharacterRef);
	}
}

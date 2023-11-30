// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/BTAnimationComponent.h"

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

	CharacterOwner = Cast<ACharacter>(GetOwner());
	if (!CharacterOwner)
	{
		BTLOG_ERROR("Please ONLY assign this component to ACharacter !");
	}
}

void UBTAnimationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Requirements for replicated properties
	DOREPLIFETIME(UBTAnimationComponent, bIsPlayingCombinedAnim);
	DOREPLIFETIME(UBTAnimationComponent, CurrentAnim);
}

bool UBTAnimationComponent::TryPlayCombinedAnimation(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
	if (!CanPlayCombinedAnimWithCharacter(OtherCharacter, CombineAnimTag))
	{
		return false;
	}

	PlayCombinedAnimation(OtherCharacter, CombineAnimTag);
	return true;
}

void UBTAnimationComponent::PlayCombinedAnimation_Implementation(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
	const FCombinedAnimsData* AnimsData = GetCombinedAnimData(CombineAnimTag);
	if (AnimsData && AnimsData->AttackerAnimMontage)
	{
		CurrentAnim = FCombinedAnim(*AnimsData, CombineAnimTag, OtherCharacter); // TODO: Polish code here
		// TODO(Nghia Lam): Motion wrapping here

		StartAnimOnAttacker();
		StartAnimOnReceiver();
		bIsPlayingCombinedAnim = true;
	}
}

bool UBTAnimationComponent::PlayCombinedAnimation_Validate(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
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

FCombinedAnimsData* UBTAnimationComponent::GetCombinedAnimData(const FGameplayTag& AnimTag) const
{
	const auto Anims = AnimsConfigDatabase->GetRowMap();
	for (const auto Anim : Anims)
	{
		FCombinedAnimsData* CurrentData = reinterpret_cast<FCombinedAnimsData*>(Anim.Value);
		if (CurrentData->AnimTag == AnimTag)
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

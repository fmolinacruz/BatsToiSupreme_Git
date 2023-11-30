// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/BTAnimationComponent.h"

#include "Net/UnrealNetwork.h"

UBTAnimationComponent::UBTAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void UBTAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
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
	return false;
}

void UBTAnimationComponent::PlayCombinedAnimation_Implementation(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
}

bool UBTAnimationComponent::PlayCombinedAnimation_Validate(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
	return false;
}

bool UBTAnimationComponent::CanPlayCombinedAnimWithCharacter(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
	return false;
}

bool UBTAnimationComponent::EvaluateCombinedAnim(const FCombinedAnimsData& AnimConfig, const ACharacter* OtherChar) const
{
	return false;
}

void UBTAnimationComponent::OnCombinedAnimStarted(const FGameplayTag& AnimTag)
{
}

void UBTAnimationComponent::OnCombinedAnimEnded(const FGameplayTag& AnimTag)
{
}

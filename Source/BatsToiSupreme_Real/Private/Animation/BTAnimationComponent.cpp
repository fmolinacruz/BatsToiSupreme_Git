// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/BTAnimationComponent.h"

UBTAnimationComponent::UBTAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBTAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBTAnimationComponent::PlayCombinedAnimation_Implementation(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
}

bool UBTAnimationComponent::PlayCombinedAnimation_Validate(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag)
{
}

bool UBTAnimationComponent::EvaluateCombinedAnim(const FCombinedAnimsAttacker& AnimConfig, const ACharacter* OtherChar) const
{
}

void UBTAnimationComponent::OnCombinedAnimStarted(const FGameplayTag& AnimTag)
{
}

void UBTAnimationComponent::OnCombinedAnimEnded(const FGameplayTag& AnimTag)
{
}

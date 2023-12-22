// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTCharacterAbilityHandler.h"

#include "Animation/BTAnimationComponent.h"
#include "Characters/BTBaseCharacter.h"
#include "Utilities/BTLogging.h"

UBTCharacterAbilityHandler::UBTCharacterAbilityHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBTCharacterAbilityHandler::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<ABTBaseCharacter>(GetOwner());
	if (CharacterOwner == nullptr)
	{
		BTLOG_ERROR("[UBTCharacterAbilityHandler] - BeginPlay: This component needs to be attached to an ABTBaseCharacter!");
	}
}

ERelativeDirection UBTCharacterAbilityHandler::GetDirectionBasedOnInput(const EAbilityInputType InputType)
{
	switch (InputType)
	{
		case EAbilityInputType::LeftLight:
		case EAbilityInputType::LeftHeavy:
			return ERelativeDirection::Left;
		case EAbilityInputType::RightLight:
		case EAbilityInputType::RightHeavy:
			return ERelativeDirection::Right;
		case EAbilityInputType::Sprawl:
		default:
			return ERelativeDirection::None;
	}
}

void UBTCharacterAbilityHandler::ActivateAbility(const EAbilityInputType InputType)
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(CurrentInputTags[InputType]);
	CharacterOwner->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
	CharacterOwner->GetAnimationHandler()->TryPlayCombinedAnimation(CharacterOwner->BTEnemy, CurrentInputTags[InputType], GetDirectionBasedOnInput(InputType));
}

void UBTCharacterAbilityHandler::ProcessNewInputDecision(const EAbilityInputType InputType, const FGameplayTag& NewInputTags)
{
	CurrentInputTags[InputType] = NewInputTags;
}

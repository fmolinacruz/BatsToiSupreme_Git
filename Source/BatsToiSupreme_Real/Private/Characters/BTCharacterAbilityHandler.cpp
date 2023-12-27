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

ERelativeDirection UBTCharacterAbilityHandler::GetDirectionBasedOnTag(const FGameplayTag AbilityTag)
{
	for (auto t : CurrentInputTags)
	{
		if (t.Value == AbilityTag)
		{
			return GetDirectionBasedOnInput(t.Key);
		}
	}
	return ERelativeDirection::None;
}

void UBTCharacterAbilityHandler::ActivateAbilityWithInput(const EAbilityInputType InputType)
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(CurrentInputTags[InputType]);
	CharacterOwner->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
	CharacterOwner->GetAnimationHandler()->TryPlayCombinedAnimation(CharacterOwner->BTEnemy, CurrentInputTags[InputType], GetDirectionBasedOnInput(InputType));
}

void UBTCharacterAbilityHandler::ActivateAbilityWithTag(const FGameplayTag AbilityTag, const ERelativeDirection Direction)
{
	// Last effort to get the direction from current database
	const ERelativeDirection AbilityDirection = (Direction == ERelativeDirection::None) ? GetDirectionBasedOnTag(AbilityTag) : Direction;

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(AbilityTag);
	CharacterOwner->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
	CharacterOwner->GetAnimationHandler()->TryPlayCombinedAnimation(CharacterOwner->BTEnemy, AbilityTag, AbilityDirection);
}

void UBTCharacterAbilityHandler::ProcessNewInputDecision(const EAbilityInputType InputType, const FGameplayTag& NewInputTags)
{
	CurrentInputTags[InputType] = NewInputTags;
}

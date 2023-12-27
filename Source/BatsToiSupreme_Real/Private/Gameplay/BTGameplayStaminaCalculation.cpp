// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/BTGameplayStaminaCalculation.h"

#include "AbilitySystemComponent.h"
#include "Animation/BTAnimationComponent.h"
#include "Animation/CombinedAnimTypes.h"
#include "Characters/BTBaseCharacter.h"
#include "Characters/BTCharacterAttributeSet.h"
#include "Utilities/BTLogging.h"

UBTGameplayStaminaCalculation::UBTGameplayStaminaCalculation()
{
	StaminaDef.AttributeToCapture = UBTCharacterAttributeSet::GetStaminaAttribute();
	StaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StaminaDef.bSnapshot = false;

	MaxStaminaDef.AttributeToCapture = UBTCharacterAttributeSet::GetMaxStaminaAttribute();
	MaxStaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxStaminaDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(StaminaDef);
	RelevantAttributesToCapture.Add(MaxStaminaDef);
}

float UBTGameplayStaminaCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const ABTBaseCharacter* Character = Cast<ABTBaseCharacter>(Spec.GetContext().GetInstigator());
	if (Character == nullptr)
	{
		BTLOG_WARNING("[UBTGameplayStaminaCalculation] - CalculateBaseMagnitude: Need to use ABTBaseCharacter!");
		return 0.0f;
	}

	const FCombinedAnim CurrentAnimationData = Character->GetAnimationHandler()->GetCurrentAnimationData();
	return CurrentAnimationData.AnimData.StaminaUsage;
}

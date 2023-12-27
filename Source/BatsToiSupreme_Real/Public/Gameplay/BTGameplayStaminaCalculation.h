// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "BTGameplayStaminaCalculation.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API UBTGameplayStaminaCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UBTGameplayStaminaCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	FGameplayEffectAttributeCaptureDefinition StaminaDef;
	FGameplayEffectAttributeCaptureDefinition MaxStaminaDef;
};

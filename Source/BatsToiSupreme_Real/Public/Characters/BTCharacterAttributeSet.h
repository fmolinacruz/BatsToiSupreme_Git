// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Attributes/GSCAttributeSetBase.h"
#include "BTCharacterAttributeSet.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API UBTCharacterAttributeSet : public UGSCAttributeSetBase
{
	GENERATED_BODY()

public:
	UBTCharacterAttributeSet();

	// AttributeSet Overrides
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * Current stamina, used to execute abilities. Capped by MaxStamina.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "BatstoiCharacter|AttributeSet", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina = 0.0f;
	ATTRIBUTE_ACCESSORS(UBTCharacterAttributeSet, Stamina)

	/**
	 * MaxHealth is its own attribute since GameplayEffects may modify it
	 */
	UPROPERTY(BlueprintReadOnly, Category = "BatstoiCharacter|AttributeSet", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina = 0.0f;
	ATTRIBUTE_ACCESSORS(UBTCharacterAttributeSet, MaxStamina)

	/**
	 * Stamina regen rate will passively increase Stamina every period
	 */
	UPROPERTY(BlueprintReadOnly, Category = "BatstoiCharacter|AttributeSet", ReplicatedUsing = OnRep_StaminaRegenRate)
	FGameplayAttributeData StaminaRegenRate = 0.0f;
	ATTRIBUTE_ACCESSORS(UBTCharacterAttributeSet, StaminaRegenRate)

protected:
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
	
	UFUNCTION()
	virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate);
	
	virtual float GetClampMinimumValueOfAttribute(const FGameplayAttribute& Attribute);
	virtual void SetAttributeClamped(const FGameplayAttribute& Attribute, const float Value, const float MaxValue);
	virtual void HandleStaminaAttribute(const FGSCAttributeSetExecutionData& ExecutionData);
};

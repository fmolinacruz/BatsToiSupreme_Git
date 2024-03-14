// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BTCharacterAttributeSet.h"

#include "Components/GSCCoreComponent.h"
#include "Net/UnrealNetwork.h"

UBTCharacterAttributeSet::UBTCharacterAttributeSet()
{
}

void UBTCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}
}

void UBTCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGSCAttributeSetExecutionData ExecutionData;
	GetExecutionDataFromMod(Data, ExecutionData);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		HandleStaminaAttribute(ExecutionData);
	}
}

void UBTCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBTCharacterAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBTCharacterAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBTCharacterAttributeSet, StaminaRegenRate, COND_None, REPNOTIFY_Always);
}

void UBTCharacterAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBTCharacterAttributeSet, Stamina, OldStamina);
}

void UBTCharacterAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBTCharacterAttributeSet, MaxStamina, OldMaxStamina);
}

void UBTCharacterAttributeSet::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBTCharacterAttributeSet, StaminaRegenRate, OldStaminaRegenRate);
}

float UBTCharacterAttributeSet::GetClampMinimumValueOfAttribute(const FGameplayAttribute& Attribute)
{
	// Does any other attribute min values is less than 0?
	return 0.0f;
}

void UBTCharacterAttributeSet::SetAttributeClamped(const FGameplayAttribute& Attribute, const float Value, const float MaxValue)
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	const float Min = GetClampMinimumValueOfAttribute(Attribute);
	const float NewValue = FMath::Clamp(Value, Min, MaxValue);

	ASC->SetNumericAttributeBase(Attribute, NewValue);
}

void UBTCharacterAttributeSet::HandleStaminaAttribute(const FGSCAttributeSetExecutionData& ExecutionData)
{
	UGSCCoreComponent* TargetCoreComponent = ExecutionData.TargetCoreComponent;
	
	const float ClampMinimumValue = GetClampMinimumValueFor(GetStaminaAttribute());
	SetStamina(FMath::Clamp(GetStamina(), ClampMinimumValue, GetMaxStamina()));
	
	if (TargetCoreComponent)
	{
		const float DeltaValue = ExecutionData.DeltaValue;
		const FGameplayTagContainer SourceTags = ExecutionData.SourceTags;
		TargetCoreComponent->HandleStaminaChange(DeltaValue, SourceTags);
	}
}

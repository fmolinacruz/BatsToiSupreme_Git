// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "BTCharacterAbilityHandler.generated.h"

enum class ERelativeDirection : uint8;

class ABTBaseCharacter;

UENUM(BlueprintType)
enum class EAbilityInputType : uint8
{
	LeftLight,
	LeftHeavy,
	RightLight,
	RightHeavy,
	Sprawl
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTCharacterAbilityHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UBTCharacterAbilityHandler();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|Ability")
	void ActivateAbilityWithInput(const EAbilityInputType InputType);
	
	UFUNCTION(BlueprintCallable, Category = "Batstoi|Ability")
	void ActivateAbilityWithTag(const FGameplayTag& AbilityTag, const ERelativeDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "Batstoi|Ability")
	void ProcessNewInputDecision(const EAbilityInputType InputType, const FGameplayTag& NewInputTags);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Batstoi|Ability")
	ERelativeDirection GetDirectionBasedOnInput(const EAbilityInputType InputType);
	
	UFUNCTION(BlueprintCallable, Category = "Batstoi|Ability")
	ERelativeDirection GetDirectionBasedOnTag(const FGameplayTag AbilityTag);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Ability")
	TMap<EAbilityInputType, FGameplayTag> CurrentInputTags;

private:
	TObjectPtr<ABTBaseCharacter> CharacterOwner;
};

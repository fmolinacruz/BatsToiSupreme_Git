// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "CombinedAnimTypes.generated.h"

UENUM(BlueprintType)
enum class ERelativePosition : uint8
{
	Any UMETA(DisplayName = "Any position"),
	SyncBone UMETA(DisplayName = "Sync bone's position"),
};

UENUM(BlueprintType)
enum class ERelativeDirection : uint8
{
	Left UMETA(DisplayName = "Left Direction"),
	Right UMETA(DisplayName = "Right Direction"),
	None UMETA(DisplayName = "No Direction")
};

USTRUCT(BlueprintType)
struct FCombinedAnimsData : public FTableRowBase
{
	GENERATED_BODY()

	/* The tag of this combined anim */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi")
	FGameplayTag AnimTag;

	/* The montage to be played on attacker */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi")
	TObjectPtr<UAnimMontage> AttackerAnimMontage;

	/* The montage to be played on receiver */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi")
	TObjectPtr<UAnimMontage> ReceiverAnimMontage;

	/* The direction of the anim to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi")
	ERelativeDirection AnimDirection = ERelativeDirection::Left;

	/* The receiver will be move to this position when the animation start */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi")
	ERelativePosition ReceiverForcePosition = ERelativePosition::Any;

	/* The stamina to trigger this ability */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi")
	float StaminaUsage;
};

USTRUCT(BlueprintType)
struct FCombinedAnim
{
	GENERATED_BODY()

	FCombinedAnim() {};

	FCombinedAnim(const FCombinedAnimsData& InAnimData, const FGameplayTag& InTag, ACharacter* InCharacterRef)
	{
		AnimData = InAnimData;
		AnimTag = InTag;
		ReceiverCharacterRef = InCharacterRef;
	}

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|Combined Animation")
	FCombinedAnimsData AnimData;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|Combined Animation")
	FGameplayTag AnimTag;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|Combined Animation")
	TObjectPtr<ACharacter> ReceiverCharacterRef;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "CombinedAnimTypes.generated.h"

UENUM(BlueprintType)
enum class ERelativePosition : uint8
{
	EAny UMETA(DisplayName = "Any position"),
	ESyncBone UMETA(DisplayName = "Get references from the sync bone"),
};

UENUM(BlueprintType)
enum class ERelativeDirection : uint8
{
	ELeft UMETA(DisplayName = "Left Direction"),
	ERight UMETA(DisplayName = "Right Direction"),
};

USTRUCT(BlueprintType)
struct FCombinedAnimsAttacker : public FTableRowBase
{
	GENERATED_BODY()

public:
	/* The tag of this combined anim */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Combined Animation")
	FGameplayTag AnimTag;

	/* The montage to be played on attacker */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Combined Animation")
	class UAnimMontage* AttackerAnimMontage;

	/* The direction of the anim to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Combined Animation")
	ERelativeDirection AnimDirection = ERelativeDirection::ELeft;

	/* The receiver will be move to this position when the animation start */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Combined Animation")
	ERelativePosition ReceiverForcePosition = ERelativePosition::EAny;
};

USTRUCT(BlueprintType)
struct FCombinedAnimsReceiver : public FTableRowBase
{
	GENERATED_BODY()

public:
	/* The tag of this combined anim */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Combined Animation")
	FGameplayTag AnimTag;

	/* The montage to be played on receiver */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Combined Animation")
	class UAnimMontage* ReceiverAnimMontage;
	
	/* The direction of the anim to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Combined Animation")
	ERelativeDirection AnimDirection = ERelativeDirection::ELeft;
};

USTRUCT(BlueprintType)
struct FCombinedAnim
{
	GENERATED_BODY()

public:
	FCombinedAnim() {};

	FCombinedAnim(const FCombinedAnimsAttacker& InAttackerConfig, const FGameplayTag& InTag, ACharacter* InCharacterRef)
	{
		AttackerAnimConfig = InAttackerConfig;
		AnimTag = InTag;
		ReceiverCharacterRef = InCharacterRef;
	}

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|Combined Animation")
	FCombinedAnimsAttacker AttackerAnimConfig;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|Combined Animation")
	FGameplayTag AnimTag;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|Combined Animation")
	TObjectPtr<ACharacter> ReceiverCharacterRef;
};

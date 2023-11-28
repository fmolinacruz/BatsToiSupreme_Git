// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombinedAnimTypes.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "BTAnimationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombinedAnimationStarted, const FGameplayTag&, animTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombinedAnimationEnded, const FGameplayTag&, animTag);

struct FCombinedAnimsAttacker;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBTAnimationComponent();

	/**
	 * Tries to play the animation tagged as combineAnimationTag with OtherCharacter and returns whether
	 * this operation is successful
	 * @param OtherCharacter - The other character to play the receiver animation
	 * @param CombineAnimTag - The anim tag that need to be played.
	 * @return - Is this function successful in playing that animation
	 */
	UFUNCTION(BlueprintCallable, Category = "Batstoi|Animation Component")
	bool TryPlayCombinedAnimation(class ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Batstoi|Animation Component")
	void PlayCombinedAnimation(class ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag);

	UFUNCTION(BlueprintCallable, Category = "Batstoi|Animation Component")
	bool CanPlayCombinedAnimWithCharacter(ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag);

	UFUNCTION(BlueprintPure, Category = "Batstoi|Animation Component")
	FORCEINLINE bool IsPlayingCombinedAnimation() const
	{
		return bIsPlayingCombinedAnim;
	}

	UFUNCTION(BlueprintPure, Category = "Batstoi|Animation Component")
	FORCEINLINE ACharacter* GetCharacterOwner() const
	{
		return CharacterOwner;
	}

	UFUNCTION(BlueprintPure, Category = "Batstoi|Animation Component")
	FORCEINLINE ACharacter* GetCharacterReceiver() const
	{
		return CurrentAnim.ReceiverCharacterRef;
	}

	UPROPERTY(BlueprintAssignable, Category = "Batstoi|Animation Component")
	FOnCombinedAnimationStarted OnCombinedAnimationStarted;

	UPROPERTY(BlueprintAssignable, Category = "Batstoi|Animation Component")
	FOnCombinedAnimationEnded OnCombinedAnimationEnded;

protected:
	virtual void BeginPlay() override;
	virtual bool EvaluateCombinedAnim(const FCombinedAnimsAttacker& AnimConfig, const ACharacter* OtherChar) const;
	virtual void OnCombinedAnimStarted(const FGameplayTag& AnimTag);
	virtual void OnCombinedAnimEnded(const FGameplayTag& AnimTag);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = CAS)
	FName WarpSyncPoint = "CombinedAnim";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = CAS)
	bool bShowWarpDebug = false;

	UPROPERTY(EditDefaultsOnly, Category = CAS)
	TObjectPtr<UDataTable> AnimsConfig;

private:
	UPROPERTY(Replicated)
	FCombinedAnim CurrentAnim;

	UPROPERTY(Replicated)
	bool bIsPlayingCombinedAnim = false;

	TObjectPtr<ACharacter> CharacterOwner;
};

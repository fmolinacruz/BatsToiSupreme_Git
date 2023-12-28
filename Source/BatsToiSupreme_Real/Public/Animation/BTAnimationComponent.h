// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombinedAnimTypes.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "BTAnimationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombinedAnimationStarted, const FGameplayTag&, animTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombinedAnimationEnded, const FGameplayTag&, animTag);

struct FCombinedAnimsData;

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
	 * @param Direction - Direction of the animation.
	 * @return - Is this function successful in playing that animation
	 */
	UFUNCTION(BlueprintCallable, Category = "Batstoi|Animation Component")
	bool TryPlayCombinedAnimation(class ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag, const ERelativeDirection& Direction);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Batstoi|Animation Component")
	void PlayCombinedAnimation(class ACharacter* OtherCharacter, const FGameplayTag& CombineAnimTag, const ERelativeDirection& Direction);

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
	
	UFUNCTION(BlueprintPure, Category = "Batstoi|Animation Component")
	FORCEINLINE FCombinedAnim& GetCurrentAnimationData()
	{
		return CurrentAnim;
	}

	UPROPERTY(BlueprintAssignable, Category = "Batstoi|Animation Component")
	FOnCombinedAnimationStarted OnCombinedAnimationStarted;

	UPROPERTY(BlueprintAssignable, Category = "Batstoi|Animation Component")
	FOnCombinedAnimationEnded OnCombinedAnimationEnded;

protected:
	virtual void BeginPlay() override;
	virtual bool EvaluateCombinedAnim(const FCombinedAnimsData& AnimConfig, const ACharacter* OtherChar) const;
	virtual void OnCombinedAnimStarted(const FGameplayTag& AnimTag);
	virtual void OnCombinedAnimEnded(const FGameplayTag& AnimTag);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Batstoi|Animation Component")
	FName WarpSyncPoint = "CombinedAnim";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Batstoi|Animation Component")
	bool bShowWarpDebug = false;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi|Animation Component")
	TObjectPtr<UDataTable> AnimsConfigDatabase;

private:
	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = CAS)
	void MulticastPlayAnimMontage(class UAnimMontage* AnimMontage, class ACharacter* Character);
	
	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = "Batstoi|Animation Component")
	void DispatchAnimStart(const FGameplayTag& AnimTag);
	
	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = "Batstoi|Animation Component")
	void DispatchAnimEnded(const FGameplayTag& AnimTag);

	UFUNCTION(BlueprintCallable)
	void HandleMontageFinished(UAnimMontage* InMontage, bool bIsInterrupted);

	FCombinedAnimsData* GetCombinedAnimData(const FGameplayTag& AnimTag, const ERelativeDirection Direction) const;
	void StartAnimOnAttacker();
	void StartAnimOnReceiver();

	UPROPERTY(Replicated)
	FCombinedAnim CurrentAnim;

	UPROPERTY(Replicated)
	bool bIsPlayingCombinedAnim = false;

	TObjectPtr<ACharacter> CharacterOwner;
};

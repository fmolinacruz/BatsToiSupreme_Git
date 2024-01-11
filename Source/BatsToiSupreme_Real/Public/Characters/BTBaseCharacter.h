// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/CombinedAnimTypes.h"
#include "Characters/BTCharacterAbilityHandler.h"
#include "ModularGameplayActors/GSCModularCharacter.h"
#include "BTBaseCharacter.generated.h"

class UMotionWarpingComponent;
class UBTCharacterMovement;
class UBTAnimationComponent;

UCLASS()
class BATSTOISUPREME_REAL_API ABTBaseCharacter : public AGSCModularCharacter
{
	GENERATED_BODY()

public:
	ABTBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void AddMovementBuffer(const FVector2D& MovementVector);
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void RefreshMovementBuffer();

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void SetCanAdjustRotation(const bool NewCanAdjust);
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void RotateTowardEnemy(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Ability")
	void HandleTriggerAbilityInput(const EAbilityInputType InputType);
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Ability")
	void HandleTriggerAbilityTag(const FGameplayTag AbilityTag, const ERelativeDirection Direction = ERelativeDirection::None);

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|PlayerID")
	void SetPlayerIndex(int32 NewIndex);

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	FORCEINLINE UBTCharacterAbilityHandler* GetAbilityHandler() const
	{
		return BTAbilityHandler;
	}
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	FORCEINLINE UBTAnimationComponent* GetAnimationHandler() const
	{
		return BTAnimationHandler;
	}
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	FORCEINLINE UMotionWarpingComponent* GetMotionWarp() const
	{
		return BTMotionWarp;
	}

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "BatstoiCharacter|Movement")
	float MovementBufferX;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "BatstoiCharacter|Movement")
	float MovementBufferY;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	bool bIsTurningRight;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	bool bIsTurningLeft;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "BatstoiCharacter|Enemy")
	TObjectPtr<ABTBaseCharacter> BTEnemy;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "BatstoiCharacter|PlayerID")
	int32 PlayerIndex;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "BatstoiCharacter|Attribute")
	float StaminaAttribute = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Attribute")
	float GetStaminaProgress() const;

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Attribute")
	void SetStaminaProgress(float value);

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Attribute")
	void SetStaminaConsumption(float value);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	bool bCanAdjustRotation = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	float AutoTurningRate = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UBTCharacterAbilityHandler> BTAbilityHandler;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UBTAnimationComponent> BTAnimationHandler;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UMotionWarpingComponent> BTMotionWarp;

private:
	UFUNCTION(Server, Unreliable)
	void Server_AddMovementBuffer(ABTBaseCharacter* InCharacter, const FVector2D& MovementVector);

	UFUNCTION(Server, Unreliable)
	void Server_RefreshMovementBuffer(ABTBaseCharacter* InCharacter);

	UFUNCTION(Server, Unreliable)
	void Server_RotateTowardEnemy(ABTBaseCharacter* InCharacter, float DeltaSeconds);
	
	static void Internal_RotateTowardEnemy(ABTBaseCharacter* InCharacter, float DeltaSeconds);
};

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
class UBTCharacterAttachmentRef;

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

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|CharacterID")
	void SetCharacterID(int32 NewIndex);

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
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	FORCEINLINE UBTCharacterAttachmentRef* GetAnimTransformRef() const
	{
		return BTAnimTransformRef;
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

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "BatstoiCharacter|PlayerID")
	int32 CharacterID;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "BatstoiCharacter|Attribute")
	float StaminaAttribute = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Attribute")
	float GetStaminaProgress() const;

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Attribute")
	void SetStaminaProgress(float value);

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Attribute")
	void SetStaminaConsumption(float value);

	// void SetCharacterID
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|CharacterIndex")
	void SetCharacterIndex(int32 NewCharacterIndex) { MyCharacterIndexCPP = NewCharacterIndex; }

	// int32 GetCharacterID
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|CharacterIndex")
	int32 GetCharacterIndex() const { return MyCharacterIndexCPP; }
	
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
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UBTCharacterAttachmentRef> BTAnimTransformRef;

	// The timer handle used for the delay
	FTimerHandle MashCountingTimerHandle;

	// The amount of times the button has been mashed
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Mash")
	int32 MashAmountCPP = 0;

	// Whether the button mashing is currently being counted
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Mash")
	bool MashingCPP = false;

	// IsReceivingDecision
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Decision")
	bool IsReceivingDecisionCPP = false;

	// ChargeInput
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Decision")
	bool ChargeInputCPP = true;

	// string InputDirection
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Decision")
	FString InputDirectionCPP;

	// string InputType
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Decision")
	FString InputTypeCPP;

	// float StallingProgress
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Decision")
	float StallingProgressCPP = 0.0f;

	// bool CanHold
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Decision")
	bool CanHoldCPP = true;

	// int32 MyCharacterIndex
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|CharacterIndex")
	int32 MyCharacterIndexCPP;


protected:
	// Function to stop button mash counting after a delay
	UFUNCTION()
	void StopButtonMashCountingCPP();

private:
	UFUNCTION(Server, Unreliable)
	void Server_AddMovementBuffer(ABTBaseCharacter* InCharacter, const FVector2D& MovementVector);

	UFUNCTION(Server, Unreliable)
	void Server_RefreshMovementBuffer(ABTBaseCharacter* InCharacter);

	UFUNCTION(Server, Unreliable)
	void Server_RotateTowardEnemy(ABTBaseCharacter* InCharacter, float DeltaSeconds);
	
	static void Internal_RotateTowardEnemy(ABTBaseCharacter* InCharacter, float DeltaSeconds);

public:
	// Function to start button mash counting
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Mash")
	void StartButtonMashCountingCPP(float Duration);
};

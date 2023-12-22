// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTCharacterMovement.h"
#include "ModularGameplayActors/GSCModularCharacter.h"
#include "BTBaseCharacter.generated.h"

class UBTCharacterAbilityHandler;
class UBTCharacterMovement;

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
	void RotateTowardEnemy(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	FORCEINLINE UBTCharacterAbilityHandler* GetAbilityHandler() const
	{
		return BTAbilityHandler;
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
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	float AutoTurningRate = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UBTCharacterAbilityHandler> BTAbilityHandler;

private:
	UFUNCTION(Server, Unreliable)
	void Server_AddMovementBuffer(ABTBaseCharacter* InCharacter, const FVector2D& MovementVector);

	UFUNCTION(Server, Unreliable)
	void Server_RefreshMovementBuffer(ABTBaseCharacter* InCharacter);

	UFUNCTION(Server, Unreliable)
	void Server_RotateTowardEnemy(ABTBaseCharacter* InCharacter, float DeltaSeconds);
	
	static void Internal_RotateTowardEnemy(ABTBaseCharacter* InCharacter, float DeltaSeconds);
};

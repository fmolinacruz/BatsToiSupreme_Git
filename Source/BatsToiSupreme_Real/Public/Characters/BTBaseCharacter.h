// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTCharacterMovement.h"
#include "ModularGameplayActors/GSCModularCharacter.h"
#include "BTBaseCharacter.generated.h"

class UBTCharacterMovement;

UCLASS()
class BATSTOISUPREME_REAL_API ABTBaseCharacter : public AGSCModularCharacter
{
	GENERATED_BODY()

public:
	ABTBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void AddMovementBuffer(const FVector2D& MovementVector);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddMovementBuffer(const FVector2D& MovementVector);
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void RefreshMovementBuffer();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RefreshMovementBuffer();

	UPROPERTY(Replicated, BlueprintReadOnly)
	FVector MovementVelocity;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bIsTurningRight;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bIsTurningLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Enemy")
	TObjectPtr<ABTBaseCharacter> BTEnemy;

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void RotateTowardEnemy(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Movement")
	void PerformRotation(float DeltaSeconds);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RotateTowardEnemy(float DeltaSeconds);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Rotation")
	float AutoTurningRate = 50.0f;
	
private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

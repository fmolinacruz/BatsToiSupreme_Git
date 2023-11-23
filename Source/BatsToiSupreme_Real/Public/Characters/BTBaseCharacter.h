// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BTBaseCharacter.generated.h"

class UBTCharacterMovement;

UCLASS()
class BATSTOISUPREME_REAL_API ABTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABTBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	UBTCharacterMovement* GetBTMovementComponent() const { return BTMovementComponent; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UBTCharacterMovement> BTMovementComponent;
};

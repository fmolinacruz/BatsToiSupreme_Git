// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BTBaseCharacter.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API ABTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABTBaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

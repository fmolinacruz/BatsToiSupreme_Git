// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BTCharacterMovement.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UBTCharacterMovement(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

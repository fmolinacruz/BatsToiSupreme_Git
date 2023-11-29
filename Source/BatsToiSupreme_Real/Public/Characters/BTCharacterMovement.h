// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTCharacterMovement.generated.h"

UINTERFACE(BlueprintType)
class UBTCharacterMovement : public UInterface
{
	GENERATED_BODY()
};

class IBTCharacterMovement
{
	GENERATED_BODY()
	
public:
	virtual const FVector GetMovementVelocity() = 0;
};

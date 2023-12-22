// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BTCharacterAbilityHandler.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTCharacterAbilityHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UBTCharacterAbilityHandler();

protected:
	virtual void BeginPlay() override;
};

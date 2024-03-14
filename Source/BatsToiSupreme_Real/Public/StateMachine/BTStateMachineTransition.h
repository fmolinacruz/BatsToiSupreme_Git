// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Utilities/Graph/BTGraphEdge.h"
#include "BTStateMachineTransition.generated.h"

class UBTGraphCondition;

UCLASS()
class BATSTOISUPREME_REAL_API UBTStateMachineTransition : public UBTGraphEdge
{
	GENERATED_BODY()

public:
	FORCEINLINE FGameplayTag GetTransitionTag() const
	{
		return TransitionTag;
	}

	bool VerifyTransitionConditions();

protected:
	UPROPERTY(EditDefaultsOnly, Category = BTSM)
	FGameplayTag TransitionTag;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = BTSM)
	TArray<TObjectPtr<UBTGraphCondition>> Conditions;
};

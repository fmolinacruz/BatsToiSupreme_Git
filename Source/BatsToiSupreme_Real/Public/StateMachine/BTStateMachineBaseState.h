// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "BTStateMachineBaseState.generated.h"

class UBTStateMachine;

UCLASS()
class BATSTOISUPREME_REAL_API UBTStateMachineBaseState : public UObject
{
	GENERATED_BODY()

public:
	UBTStateMachineBaseState();

	UFUNCTION(BlueprintCallable, Category = BTSM)
	bool TriggerTransition(const FGameplayTag& TransitionTag);

	UFUNCTION(BlueprintNativeEvent, Category = BTSM)
	void OnEnter();
	
	UFUNCTION(BlueprintNativeEvent, Category = BTSM)
	void OnExit();
	
	UFUNCTION(BlueprintNativeEvent, Category = BTSM)
	void OnUpdate();
	
	UFUNCTION(BlueprintNativeEvent, Category = BTSM)
	void OnTransition(const UBTStateMachineBaseState* PreviousState);

	UFUNCTION(BlueprintPure, Category = BTSM)
	FORCEINLINE UBTStateMachine* GetStateMachineOwner() const
	{
		return FSMOwner;
	}
	
	UFUNCTION(BlueprintCallable, Category = BTSM)
	FORCEINLINE void SetStateMachineOwner(UBTStateMachine* StateMachine)
	{
		if (FSMOwner == nullptr)
		{
			FSMOwner = StateMachine;
		}
	}

protected:
	virtual void OnEnter_Implementation();
	virtual void OnExit_Implementation();
	virtual void OnUpdate_Implementation();
	virtual void OnTransition_Implementation(const UBTStateMachineBaseState* PreviousState);

private:
	TObjectPtr<UBTStateMachine> FSMOwner;
};

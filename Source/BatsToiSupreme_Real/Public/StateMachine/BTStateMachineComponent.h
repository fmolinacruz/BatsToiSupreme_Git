// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachine/BTStateMachine.h"
#include "BTStateMachineComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBTStateMachineComponent();

	/**
	 * Replicated version of the StartFSM function.
	 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = BTSM)
	void SyncedStartFSM();
	
	/**
	 * Replicated version of the StopFSM function.
	 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = BTSM)
	void SyncedStopFSM();

	UFUNCTION(BlueprintPure, Category = BTSM)
	FORCEINLINE bool IsFSMActive() const
	{
		return FSM ? FSM->IsActive() : false;
	}

	UFUNCTION(BlueprintPure, Category = BTSM)
	FORCEINLINE bool IsFSMTickEveryFrame() const
	{
		return bCanFSMTick;
	}

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PostInitProperties() override;
	
	UFUNCTION(BlueprintCallable, Category = BTSM)
	void StartFSM() const;
	
	UFUNCTION(BlueprintCallable, Category = BTSM)
	void StopFSM() const;
	
	// The actual FSM
	UPROPERTY(EditDefaultsOnly, Category = BTSM)
	TObjectPtr<UBTStateMachine> FSM;

	// Sets if this FSM should tick
	UPROPERTY(EditDefaultsOnly, Category = BTSM)
	bool bCanFSMTick = false;
};

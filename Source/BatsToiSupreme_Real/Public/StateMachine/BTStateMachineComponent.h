// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BTStateMachineComponent.generated.h"

class UBTStateMachine;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBTStateMachineComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PostInitProperties() override;
	
	// The actual FSM
	UPROPERTY(EditDefaultsOnly, Category = BTSM)
	TObjectPtr<UBTStateMachine> FSM;

	// Sets if this FSM should tick
	UPROPERTY(EditDefaultsOnly, Category = BTSM)
	bool bCanFSMTick = false;
};

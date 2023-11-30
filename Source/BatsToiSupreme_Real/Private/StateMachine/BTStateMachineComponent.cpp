// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/BTStateMachineComponent.h"

#include "StateMachine/BTStateMachine.h"

UBTStateMachineComponent::UBTStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBTStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBTStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FSM && FSM->IsActive())
	{
		FSM->DispatchTick(DeltaTime);
	}
}

void UBTStateMachineComponent::PostInitProperties()
{
	Super::PostInitProperties();
	SetComponentTickEnabled(bCanFSMTick);
	SetIsReplicatedByDefault(true);
}

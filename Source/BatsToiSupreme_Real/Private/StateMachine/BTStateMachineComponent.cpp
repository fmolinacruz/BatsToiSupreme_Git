// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/BTStateMachineComponent.h"

#include "Utilities/BTLogging.h"

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

void UBTStateMachineComponent::SyncedStartFSM_Implementation()
{
	StartFSM();
}

void UBTStateMachineComponent::SyncedStopFSM_Implementation()
{
	StopFSM();
}

void UBTStateMachineComponent::StartFSM() const
{
	if (FSM)
	{
		FSM->StartFSM(GetOwner());
	}
	else
	{
		BTLOG_ERROR("[UBTStateMachineComponent] - StartFSM: Invalid state machine reference!");
	}
}

void UBTStateMachineComponent::StopFSM() const
{
	if (FSM)
	{
		FSM->StopFSM();
	}
	else
	{
		BTLOG_ERROR("[UBTStateMachineComponent] - StopFSM: Invalid state machine reference!");
	}
}

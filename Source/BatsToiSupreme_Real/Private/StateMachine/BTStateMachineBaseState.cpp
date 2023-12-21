// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/BTStateMachineBaseState.h"

#include "StateMachine/BTStateMachine.h"

UBTStateMachineBaseState::UBTStateMachineBaseState()
	: FSMOwner(nullptr)
{
}

bool UBTStateMachineBaseState::TriggerTransition(const FGameplayTag& TransitionTag)
{
	if (FSMOwner)
	{
		return FSMOwner->TransitionNode(TransitionTag);
	}
	return false;
}

void UBTStateMachineBaseState::OnEnter_Implementation()
{
}

void UBTStateMachineBaseState::OnExit_Implementation()
{
}

void UBTStateMachineBaseState::OnUpdate_Implementation()
{
}

void UBTStateMachineBaseState::OnTransition_Implementation(const UBTStateMachineBaseState* PreviousState)
{
}

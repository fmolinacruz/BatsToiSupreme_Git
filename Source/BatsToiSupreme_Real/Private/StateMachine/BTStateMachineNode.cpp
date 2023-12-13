// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/BTStateMachineNode.h"

#include "StateMachine/BTStateMachine.h"
#include "StateMachine/BTStateMachineBaseState.h"
#include "Utilities/BTLogging.h"

UBTStateMachineNode::UBTStateMachineNode()
{
}

void UBTStateMachineNode::ActivateNode()
{
	Super::ActivateNode();

	UBTStateMachine* StatemachineOwner = Cast<UBTStateMachine>(GetGraph());
	if (OwningState && StatemachineOwner)
	{
		OwningState->SetStateMachineOwner(StatemachineOwner);
		OwningState->OnEnter();
	}
	else
	{
		BTLOG_WARNING("[UBTStateMachineNode] - ActivateNode: Invalid State");
	}
}

void UBTStateMachineNode::DeactivateNode()
{
	Super::DeactivateNode();
	if (OwningState)
	{
		OwningState->OnExit();
	}
	else
	{
		BTLOG_WARNING("[UBTStateMachineNode] - DeactivateNode: Invalid State");
	}
}

void UBTStateMachineNode::Transition(const UBTStateMachineBaseState* PreviousState)
{
	if (OwningState)
	{
		OwningState->OnTransition(PreviousState);
	}
	else
	{
		BTLOG_WARNING("[UBTStateMachineNode] - Transition: Invalid State");
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/BTStateMachine.h"

#include "StateMachine/BTStateMachineNode.h"
#include "Utilities/BTLogging.h"

UBTStateMachine::UBTStateMachine()
{
	NodeType = UBTStateMachineNode::StaticClass();
	bHasStarted = false;
}

void UBTStateMachine::StartFSM(AActor* InOwner)
{
	if (InOwner == nullptr)
	{
		BTLOG_WARNING("StateMachine Owner cannot be null!");
		return;
	}
	
	StateMachineOwner = InOwner;
	if (IsActive())
	{
		BTLOG_ERROR("StateMachine has already started!")
		return;
	}

	Internal_Start();
}

void UBTStateMachine::StopFSM()
{
	if (IsActive())
	{
		DeactivateAllNodes();
		bHasStarted = false;
	}
	else
	{
		BTLOG_WARNING("StateMachine hasn't started yet!")
	}
}

void UBTStateMachine::DispatchTick(float DeltaTime)
{
	if (CurrentState)
	{
		// TODO: Dispatch Tick for each state.
	}
}

bool UBTStateMachine::ActivateNode(UBTGraphNode* Node)
{
	CurrentState = Cast<UBTStateMachineNode>(Node);
	if (!CurrentState)
	{
		BTLOG_ERROR("This StateMachine graph didn't have the correct node type!");
		return false;
	}
	
	return Super::ActivateNode(Node);
}

void UBTStateMachine::Internal_Start()
{
	// TODO: Start the state machine.
}

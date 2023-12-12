// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/BTStateMachine.h"

#include "StateMachine/BTStateMachineNode.h"
#include "StateMachine/BTStateMachineTransition.h"
#include "Utilities/BTLogging.h"

UBTStateMachine::UBTStateMachine()
{
	NodeType = UBTStateMachineNode::StaticClass();
	EdgeType = UBTStateMachineTransition::StaticClass();
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
	if (CurrentNode)
	{
		// TODO: Dispatch Tick for each state.
	}
}

bool UBTStateMachine::ActivateNode(UBTGraphNode* Node)
{
	CurrentNode = Cast<UBTStateMachineNode>(Node);
	if (!CurrentNode)
	{
		BTLOG_ERROR("This StateMachine graph didn't have the correct node type!");
		return false;
	}

	return Super::ActivateNode(Node);
}

void UBTStateMachine::Internal_Start()
{
	for (UBTGraphNode* Root : RootNodes)
	{
		UBTStateMachineNode* StateNode = Cast<UBTStateMachineNode>(Root);
		if (StateNode && StateNode->GetNodeType() == EStateMachineNodeType::Start)
		{
			ActivateNode(StateNode);
			bHasStarted = true;
			return;
		}
	}
}

bool UBTStateMachine::TransitionNode(const FGameplayTag& TransitionTag)
{
	if (!IsActive())
	{
		BTLOG_ERROR("[UBTStateMachine] - TransitionNode: StateMachine didn't start yet!")
		return false;
	}

	for (UBTGraphNode* Node : GetAllActiveNodes())
	{
		UBTStateMachineNode* StateNode = Cast<UBTStateMachineNode>(Node);
		if (StateNode == CurrentNode)
		{
			for (auto EdgeData : StateNode->EdgeDatas)
			{
				UBTStateMachineTransition* Transition = Cast<UBTStateMachineTransition>(EdgeData.Value);
				if (Transition && Transition->GetTransitionTag() == TransitionTag && Transition->VerifyTransitionConditions())
				{
					DeactivateNode(StateNode);
					UBTStateMachineNode* NextNode = Cast<UBTStateMachineNode>(EdgeData.Key);
					if (NextNode)
					{
						NextNode->Transition(StateNode->GetNodeState());
						return ActivateNode(NextNode);
					}
				}
			}
		}
	}
	return false;
}

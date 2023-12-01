// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/Graph/BTGraphNode.h"

UBTGraphNode::UBTGraphNode() {}

UBTGraphNode::~UBTGraphNode() {}

bool UBTGraphNode::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

void UBTGraphNode::ActivateNode()
{
	NodeState = ENodeState::Enabled;
}

void UBTGraphNode::DeactivateNode()
{
	NodeState = ENodeState::Disabled;
}

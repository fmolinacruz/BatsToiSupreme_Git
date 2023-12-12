// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/Graph/BTGraphNode.h"

#include "StateMachine/Graph/BTGraph.h"
#include "StateMachine/Graph/BTGraphEdge.h"

UBTGraphNode::UBTGraphNode() {}

UBTGraphNode::~UBTGraphNode() {}

bool UBTGraphNode::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

UBTGraphEdge* UBTGraphNode::GetEdgeBasedOnChildNode(const UBTGraphNode* ChildNode)
{
	if (EdgeDatas.Num() == 0)
	{
		return nullptr;
	}

	return EdgeDatas.Contains(ChildNode) ? EdgeDatas.FindChecked(ChildNode) : nullptr;
}

void UBTGraphNode::ActivateNode()
{
	NodeState = ENodeState::Enabled;
}

void UBTGraphNode::DeactivateNode()
{
	NodeState = ENodeState::Disabled;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/Graph/BTGraph.h"

#include "Utilities/Graph/BTGraphEdge.h"
#include "Utilities/Graph/BTGraphNode.h"

UBTGraph::UBTGraph()
{
	NodeType = UBTGraphNode::StaticClass();
	EdgeType = UBTGraphEdge::StaticClass();

	ActiveNodes.Empty();
}

UBTGraph::~UBTGraph() {}

bool UBTGraph::ActivateNode(UBTGraphNode* Node)
{
	if (Node && AllNodes.Contains(Node))
	{
		ActiveNodes.AddUnique(Node);
		Node->ActivateNode();
		return true;
	}
	return false;
}

bool UBTGraph::DeactivateNode(UBTGraphNode* Node)
{
	if (Node && AllNodes.Contains(Node))
	{
		ActiveNodes.Remove(Node);
		Node->DeactivateNode();
		return true;
	}
	return false;
}

void UBTGraph::DeactivateAllNodes()
{
	TArray<UBTGraphNode*> CopiedActiveNodeAddresses = GetAllActiveNodes();
	for (UBTGraphNode* Node : CopiedActiveNodeAddresses)
	{
		DeactivateNode(Node);
	}
}

void UBTGraph::ClearGraph()
{
	for (int i = 0; i < AllNodes.Num(); ++i)
	{
		UBTGraphNode* Node = AllNodes[i];

		Node->ParentNodes.Empty();
		Node->ChildrenNodes.Empty();
	}

	AllNodes.Empty();
	RootNodes.Empty();
}

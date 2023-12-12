// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BTGraphNode.generated.h"

class UBTGraph;
class UBTGraphEdge;

UENUM(BlueprintType)
enum class ENodeState : uint8
{
	Enabled,
	Disabled,
};

UCLASS()
class BATSTOISUPREME_REAL_API UBTGraphNode : public UObject
{
	GENERATED_BODY()

	friend class UBTGraph;

public:
	UBTGraphNode();
	virtual ~UBTGraphNode() override;

	UFUNCTION(BlueprintCallable, Category = "BTGraph|Node")
	bool IsLeafNode() const;

	UFUNCTION(BlueprintCallable, Category = "BTGraph|Node")
	UBTGraphEdge* GetEdgeBasedOnChildNode(const UBTGraphNode* ChildNode);

	UFUNCTION(BlueprintCallable, Category = "BTGraph|Node")
	FORCEINLINE UBTGraph* GetGraph() const
	{
		return Graph;
	}
	
	UPROPERTY(BlueprintReadOnly, Category = "BTGraph|Node")
	TMap<TObjectPtr<UBTGraphNode>, TObjectPtr<UBTGraphEdge>> EdgeDatas;

	UPROPERTY(BlueprintReadOnly, Category = "BTGraph|Node")
	TArray<UBTGraphNode*> ParentNodes;

	UPROPERTY(BlueprintReadOnly, Category = "BTGraph|Node")
	TArray<UBTGraphNode*> ChildrenNodes;

protected:
	virtual void ActivateNode();
	virtual void DeactivateNode();

	UPROPERTY(BlueprintReadOnly, Category = "BTGraph|Node")
	ENodeState NodeState = ENodeState::Disabled;

	UPROPERTY(BlueprintReadOnly, Category = "BTGraph|Node")
	TObjectPtr<UBTGraph> Graph;
};

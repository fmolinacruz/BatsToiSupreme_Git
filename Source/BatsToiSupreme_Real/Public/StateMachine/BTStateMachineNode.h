// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/BTGraphNode.h"
#include "BTStateMachineNode.generated.h"

UENUM(BlueprintType)
enum class EStateMachineNodeType : uint8
{
	Start,
	Normal
};

UCLASS()
class BATSTOISUPREME_REAL_API UBTStateMachineNode : public UBTGraphNode
{
	GENERATED_BODY()

public:
	UBTStateMachineNode();

	UFUNCTION(BlueprintCallable, Category = BTSM)
	FORCEINLINE EStateMachineNodeType GetNodeType() const
	{
		return NodeType;
	}

protected:
	UPROPERTY(BlueprintReadWrite, Category = BTSM)
	EStateMachineNodeType NodeType = EStateMachineNodeType::Normal;
};

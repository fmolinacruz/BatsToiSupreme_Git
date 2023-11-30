// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BTGraphEdge.generated.h"

class UBTGraph;
class UBTGraphNode;

UCLASS()
class BATSTOISUPREME_REAL_API UBTGraphEdge : public UObject
{
	GENERATED_BODY()

public:
	UBTGraphEdge();
	virtual ~UBTGraphEdge() override;

	UPROPERTY(BlueprintReadOnly, Category = "UBTGraph|Edge")
	TObjectPtr<UBTGraphNode> StartNode;
	
	UPROPERTY(BlueprintReadOnly, Category = "UBTGraph|Edge")
	TObjectPtr<UBTGraphNode> EndNode;

protected:
	UPROPERTY()
	TObjectPtr<UBTGraph> Graph;
};

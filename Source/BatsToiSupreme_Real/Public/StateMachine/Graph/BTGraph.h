// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BTGraph.generated.h"

class UBTGraphEdge;
class UBTGraphNode;

UCLASS(Blueprintable)
class BATSTOISUPREME_REAL_API UBTGraph : public UObject
{
	GENERATED_BODY()

public:
	UBTGraph();
	virtual ~UBTGraph() override;

	UPROPERTY(VisibleAnywhere, Category = "BTGraph")
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = "BTGraph")
	TSubclassOf<UBTGraphNode> NodeType;

	UPROPERTY(VisibleAnywhere, Category = "BTGraph")
	TSubclassOf<UBTGraphEdge> EdgeType;
};

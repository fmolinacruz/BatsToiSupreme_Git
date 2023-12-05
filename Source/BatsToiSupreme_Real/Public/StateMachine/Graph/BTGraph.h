// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "BTGraph.generated.h"

class UBTGraphEdge;
class UBTGraphNode;

/**
 * Graph implementation. Currently used for State Machine only, but we can consider
 * move these graph code somewhere else so we can re-use it for different purposes.
 */
UCLASS(Blueprintable)
class BATSTOISUPREME_REAL_API UBTGraph : public UObject
{
	GENERATED_BODY()

public:
	UBTGraph();
	virtual ~UBTGraph() override;

	UFUNCTION(BlueprintCallable, Category = "BTGraph")
	virtual bool ActivateNode(class UBTGraphNode* Node);

	UFUNCTION(BlueprintCallable, Category = "BTGraph")
	virtual bool DeactivateNode(class UBTGraphNode* Node);

	UFUNCTION(BlueprintCallable, Category = "BTGraph")
	void DeactivateAllNodes();

	UFUNCTION(BlueprintCallable, Category = "BTGraph")
	void ClearGraph();
	
	UFUNCTION(BlueprintCallable, Category = "BTGraph")
	FORCEINLINE TArray<UBTGraphNode*> GetAllNodes()
	{
		return AllNodes;
	}
	
	UFUNCTION(BlueprintCallable, Category = "BTGraph")
	FORCEINLINE TArray<UBTGraphNode*> GetAllActiveNodes()
	{
		return ActiveNodes;
	}

	UPROPERTY(VisibleAnywhere, Category = "BTGraph")
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = "BTGraph")
	TSubclassOf<UBTGraphNode> NodeType;

	UPROPERTY(VisibleAnywhere, Category = "BTGraph")
	TSubclassOf<UBTGraphEdge> EdgeType;

	UPROPERTY(VisibleAnywhere, Category = "BTGraph")
	FGameplayTagContainer GraphTags;

protected:
	// TODO: This may need to support AI Controller
	TObjectPtr<APlayerController> PlayerController;

private:
	UPROPERTY()
	TArray<UBTGraphNode*> AllNodes;
	
	UPROPERTY()
	TArray<UBTGraphNode*> ActiveNodes;
};

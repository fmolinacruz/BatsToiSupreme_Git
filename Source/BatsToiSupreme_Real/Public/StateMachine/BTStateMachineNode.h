// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/BTGraphNode.h"
#include "BTStateMachineNode.generated.h"

class UBTStateMachineBaseState;

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
	void Transition(const UBTStateMachineBaseState* PreviousState);

	UFUNCTION(BlueprintCallable, Category = BTSM)
	FORCEINLINE EStateMachineNodeType GetNodeType() const
	{
		return NodeType;
	}
	
	UFUNCTION(BlueprintCallable, Category = BTSM)
	FORCEINLINE UBTStateMachineBaseState* GetNodeState() const
	{
		return OwningState;
	}

protected:
	virtual void ActivateNode() override;
	virtual void DeactivateNode() override;
	
	UPROPERTY(BlueprintReadWrite, Category = BTSM)
	EStateMachineNodeType NodeType = EStateMachineNodeType::Normal;

	UPROPERTY(EditDefaultsOnly, Category = BTSM)
	TObjectPtr<UBTStateMachineBaseState> OwningState;
	
	UPROPERTY(EditDefaultsOnly, Category = BTSM)
	FName StateName;
};

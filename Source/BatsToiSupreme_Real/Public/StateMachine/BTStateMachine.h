// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/BTGraph.h"
#include "BTStateMachine.generated.h"

class UBTStateMachineNode;

UCLASS()
class BATSTOISUPREME_REAL_API UBTStateMachine : public UBTGraph
{
	GENERATED_BODY()

public:
	UBTStateMachine();

	UFUNCTION(BlueprintCallable, Category = BTSM)
	void StartFSM(AActor* InOwner);

	UFUNCTION(BlueprintCallable, Category = BTSM)
	void StopFSM();

	UFUNCTION(BlueprintCallable, Category = BTSM)
	FORCEINLINE bool IsActive() const
	{
		return bHasStarted;
	}

	UFUNCTION(BlueprintCallable, Category = BTSM)
	FORCEINLINE AActor* GetFSMOwner() const
	{
		return StateMachineOwner;
	}

	void DispatchTick(float DeltaTime);
	bool TransitionNode(const FGameplayTag& TransitionTag);

protected:
	virtual bool ActivateNode(UBTGraphNode* Node) override;
	
	void Internal_Start();

private:
	UPROPERTY(VisibleAnywhere, Category = BTSM)
	TObjectPtr<AActor> StateMachineOwner;

	UPROPERTY(VisibleAnywhere, Category = BTSM)
	TObjectPtr<UBTStateMachineNode> CurrentNode;

	bool bHasStarted = false;
};

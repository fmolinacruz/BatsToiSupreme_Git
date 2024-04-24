// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BTGameFunctionLibrary.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API UBTGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = BatstoiLibrary)
	static class ABTGameState* GetBTGameState(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = BatstoiLibrary)
	static class ABTGameplayManager* GetBTGameplayManager(const UObject* WorldContextObject);
};

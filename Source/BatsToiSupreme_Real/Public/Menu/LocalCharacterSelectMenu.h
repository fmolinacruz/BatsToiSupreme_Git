// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LocalCharacterSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API ULocalCharacterSelectMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	void DebugLog();
};

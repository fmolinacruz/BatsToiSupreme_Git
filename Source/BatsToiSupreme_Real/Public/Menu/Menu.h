// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Constructor
	UMenu(const FObjectInitializer& ObjectInitializer);

	// Override functions from UUserWidget
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

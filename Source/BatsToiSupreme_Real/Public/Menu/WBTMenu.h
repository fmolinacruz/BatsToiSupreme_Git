// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "WBTMenu.generated.h"

/**
 * 
 */


UCLASS()
class BATSTOISUPREME_REAL_API UWBTMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// Initialize animations
	virtual void NativeConstruct() override;

public:
	UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnim))
	UWidgetAnimation* CharacterIn1;

	UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnim))
	UWidgetAnimation* CharacterIn2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TArray<UWidgetAnimation*> CharacterAnimationsCPP;
};

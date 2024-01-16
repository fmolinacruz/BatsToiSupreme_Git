// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "WBTCharacterSelect.generated.h"

class ABTPlayerController;
class UWBTMenu;


UCLASS()
class BATSTOISUPREME_REAL_API UWBTCharacterSelect : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> PlayerColor;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNumber;

	TArray<FLinearColor> PlayerColors;
	TObjectPtr<UWBTMenu> MainMenu;
	int32 CharacterChoice;
	int32 PlayerIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	int32 SwitchCharacter(const int32 Direction);
};

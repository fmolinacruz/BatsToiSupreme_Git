// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "BTLocalInputReceiver.generated.h"

class UWBTMenu;

UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalInputReceiver : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABTLocalInputReceiver();

	void InitializeWithPlayerController(class ABTLocalPlayerController* NewPlayerController, int32 PlayerIndex);

	// Create IRCreateCharacterSelectWidget
	void CreateMenuUI();

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|PlayerController")
	TObjectPtr<ABTLocalPlayerController> CurrentPlayerController;

	// MenuWidgetRefCPP
	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UWBTMenu> MenuWidgetRefCPP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|PlayerIndex")
	int32 CurrentPlayerIndex;
	
};

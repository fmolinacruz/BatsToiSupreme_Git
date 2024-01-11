// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "BTInputReceiver.generated.h"

class UBTUISelectInput;

UCLASS()
class BATSTOISUPREME_REAL_API ABTInputReceiver : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABTInputReceiver();

	void InitializeWithPlayerController(class ABTPlayerController* NewPlayerController, int32 PlayerIndex);

public:
	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	UBTUISelectInput* GetBTUISelectionInputComponent() const { return BTUISelectionInputComponent; }

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Batstoi|UI")
	void OnCharacterSelected(int32 CharacterID);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UBTUISelectInput> BTUISelectionInputComponent;

private:
	TObjectPtr<ABTPlayerController> PlayerController;
	int32 CurrentPlayerIndex;
	bool bHasSpawnedPlayer = false;
};

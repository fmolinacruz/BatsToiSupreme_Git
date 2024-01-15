// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "BTInputReceiver.generated.h"

class UBTUISelectInput;
class UWBTMenu;

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

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnCharacterSelected();

	UFUNCTION(Server, Reliable)
	void Server_CharacterSelected();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_CharacterSelected();

	//UPROPERTY(ReplicatedUsing = OnRep_CurrentAnimationIndex)
	//int32 CurrentAnimationIndex;

	//UFUNCTION()
	//void OnRep_CurrentAnimationIndex();

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|UI")
	UWBTMenu* MenuWidgetRefCPP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Create IRCreateCharacterSelectWidget
	void CreateMenuUI();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UBTUISelectInput> BTUISelectionInputComponent;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|PlayerIndex")
	int32 CurrentPlayerIndex;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|PlayerController")
	TObjectPtr<ABTPlayerController> CurrentPlayerController;

private:
	bool bHasSpawnedPlayer = false;

protected:
	// Override replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

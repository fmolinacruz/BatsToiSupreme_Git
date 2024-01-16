// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "BTInputReceiver.generated.h"

class UBTUISelectInput;
class UWBTMenu;
class UWBTCharacterSelect;

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
	FORCEINLINE UBTUISelectInput* GetBTUISelectionInputComponent() const
	{
		return BTUISelectionInputComponent;
	}

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnCharacterSelected();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnMenuLeft();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnMenuRight();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnRestore();

	UFUNCTION(Server, Reliable)
	void Server_CharacterSelected();

	UFUNCTION(Server, Reliable)
	void Server_CharacterDecided(int32 CharacterChoice);

	UFUNCTION(Server, Reliable)
	void Server_CharacterRestore();
	
	UFUNCTION(Server, Reliable)
	void Server_CharacterChoiceChanged(int32 CharacterChoice);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_CharacterSelected();

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|PlayerController")
	TObjectPtr<ABTPlayerController> CurrentPlayerController;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|PlayerController")
	TObjectPtr<ABTPlayerController> OtherPlayerController;

	// MenuWidgetRefCPP
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UWBTMenu> MenuWidgetRefCPP;

	// CharacterMenuRefCPP
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UWBTCharacterSelect> CharacterMenuRefCPP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Create IRCreateCharacterSelectWidget
	void CreateMenuUI();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UBTUISelectInput> BTUISelectionInputComponent;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Batstoi|PlayerIndex")
	int32 CurrentPlayerIndex;

private:
	bool bHasSpawnedPlayer = false;

	bool IsReady = false;

protected:
	// Override replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

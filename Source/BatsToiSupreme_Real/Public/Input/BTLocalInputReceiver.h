// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "BTLocalInputReceiver.generated.h"

class UBTLocalUISelectInput;
class UWBTMenu;
class UWBTCharacterSelect;

UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalInputReceiver : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABTLocalInputReceiver();

	void InitializeWithPlayerController(class ABTLocalPlayerController* NewPlayerController, int32 PlayerIndex);

public:
	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	FORCEINLINE UBTLocalUISelectInput* GetBTUISelectionInputComponent() const
	{
		return BTUISelectionInputComponent;
	}

	//// Create IRCreateCharacterSelectWidget
	//void CreateMenuUI();

	void SetMenuWidget(UWBTMenu* MenuWidget);

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnCharacterSelected();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnMenuLeft();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnMenuRight();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void OnRestore();

	void Server_CharacterSelected();

	void Server_CharacterDecided(int32 CharacterChoice);

	void Server_CharacterRestore();

	void Server_CharacterChoiceChanged(int32 CharacterChoice);

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|PlayerController")
	TObjectPtr<ABTLocalPlayerController> CurrentPlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|PlayerController")
	TObjectPtr<ABTLocalPlayerController> OtherPlayerController;

	// MenuWidgetRefCPP
	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UWBTMenu> MenuWidgetRefCPP;

	// CharacterMenuRefCPP
	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UWBTCharacterSelect> CharacterMenuRefCPP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Batstoi|UI")
	TObjectPtr<UBTLocalUISelectInput> BTUISelectionInputComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Batstoi|PlayerIndex")
	int32 CurrentPlayerIndex;

private:
	bool bHasSpawnedPlayer = false;

	bool IsReady = false;
	
public:

};

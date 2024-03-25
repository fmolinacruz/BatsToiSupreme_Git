// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCommon/BTPlayerInput.h"
#include "BTUISelectInput.generated.h"

class ABTInputReceiver;
class UInputAction;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATSTOISUPREME_REAL_API UBTUISelectInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBTUISelectInput();

	// Initialize input component with enhanced input actions
	void InitializeInputComponent(UInputComponent* PlayerInputComponent);

	// InitializeWithInputReceiver
	void InitializeWithInputReceiver(ABTInputReceiver* NewInputReceiver);

public:
	// InputReceiver
	TObjectPtr<ABTInputReceiver> InputReceiver;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Actions
	void OnSelect(const FInputActionValue& Value);

	// MenuLeft
	void OnMenuLeft(const FInputActionValue& Value);

	// MenuRight
	void OnMenuRight(const FInputActionValue& Value);

	// Restore
	void Restore(const FInputActionValue& Value);

	// Input Actions
	//SelectInput
	//GamePad
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* SelectInputAction;
	//Keyboard
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* SelectInputActionKB;

	// MenuLeft
	// GamePad
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* MenuLeftInputAction;
	// Keyboard
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* MenuLeftInputActionKB;

	// MenuRight
	// GamePad
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* MenuRightInputAction;
	// Keyboard
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* MenuRightInputActionKB;

	// Restore
	// GamePad
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* RestoreInputAction;
	// Keyboard
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Batstoi|Actions")
	UInputAction* RestoreInputActionKB;

	// Mappable input configurations for the UI Selection
	UPROPERTY(EditDefaultsOnly, Category = "Batstoi|UISelectionInput")
	TArray<FMappableConfig> MappableInputConfigs;
};

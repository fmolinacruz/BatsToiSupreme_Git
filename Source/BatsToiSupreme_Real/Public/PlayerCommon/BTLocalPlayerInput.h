// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "Components/ActorComponent.h"
#include "PlayerCommon/BTPlayerInput.h"
#include "BTLocalPlayerInput.generated.h"

struct FInputActionValue;

class UInputAction;
class ABTLocalPlayerCharacter;
class UPlayerMappableInputConfig;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATSTOISUPREME_REAL_API UBTLocalPlayerInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBTLocalPlayerInput();

	void InitializeInputComponent(UInputComponent* PlayerInputComponent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Actions
	void RequestStartMovement(const FInputActionValue& Value);
	void RequestCancelMovement(const FInputActionValue& Value);
	void RequestLeftLightAction(const FInputActionValue& Value);
	void RequestLeftHeavyAction(const FInputActionValue& Value);
	void RequestRightLightAction(const FInputActionValue& Value);
	void RequestRightHeavyAction(const FInputActionValue& Value);
	void RequestSprawlAction(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput")
	TArray<FMappableConfig> DefaultInputConfigs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInput|Actions")
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInput|Actions")
	UInputAction* LeftLightInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInput|Actions")
	UInputAction* LeftHeavyInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInput|Actions")
	UInputAction* RightLightInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInput|Actions")
	UInputAction* RightHeavyInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInput|Actions")
	UInputAction* SprawlInputAction;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<ABTLocalPlayerCharacter> PlayerCharacter;
};

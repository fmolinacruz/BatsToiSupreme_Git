// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "Components/ActorComponent.h"
#include "BTPlayerInput.generated.h"

struct FInputActionValue;

class UInputAction;
class ABTPlayerCharacter;
class UPlayerMappableInputConfig;

USTRUCT()
struct FMappableConfig
{
	GENERATED_BODY()

	FMappableConfig() = default;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UPlayerMappableInputConfig> Config;

	/**
	 * The type of config that this is. Useful for filtering out configs by the current input device
	 * for things like the settings screen, or if you only want to apply this config when a certain
	 * input type is being used.
	 */
	UPROPERTY(EditAnywhere)
	ECommonInputType Type = ECommonInputType::Count;

	/**
	 * If true, then this input config will be activated when it's associated Game Feature is activated.
	 * This is normally the desirable behavior
	 */
	UPROPERTY(EditAnywhere)
	bool bShouldActivateAutomatically = true;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTPlayerInput : public UActorComponent
{
	GENERATED_BODY()

public:
	UBTPlayerInput();

	void InitializeInputComponent(UInputComponent* PlayerInputComponent);

protected:
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
	TObjectPtr<ABTPlayerCharacter> PlayerCharacter;
};

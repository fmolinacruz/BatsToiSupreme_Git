// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCommon/BTPlayerInput.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerMappableInputConfig.h"
#include "Characters/BTCharacterAbilityHandler.h"
#include "Characters/BTPlayerCharacter.h"
#include "GameModes/BTGameState.h"
#include "PlayerCommon/BTPlayerController.h"
#include "Utilities/BTGameFunctionLibrary.h"

UBTPlayerInput::UBTPlayerInput()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBTPlayerInput::BeginPlay()
{
	Super::BeginPlay();
}

void UBTPlayerInput::InitializeInputComponent(UInputComponent* PlayerInputComponent, int CharacterIndex)
{
	check(PlayerInputComponent);
	if (!PlayerCharacter)
	{
		PlayerCharacter = CastChecked<ABTPlayerCharacter>(GetOwner());
	}

	const ABTPlayerController* PC = PlayerCharacter->GetController<ABTPlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	//// Register any default input configs
	//for (const FMappableConfig& InputConfig : DefaultInputConfigs)
	//{
	//	if (InputConfig.bShouldActivateAutomatically)
	//	{
	//		FModifyContextOptions Options = {};
	//		Options.bIgnoreAllPressedKeysUntilRelease = false;

	//		Subsystem->AddPlayerMappableConfig(InputConfig.Config.LoadSynchronous(), Options);
	//	}
	//}

	// Register any default input configs
	if (CharacterIndex == 0 && GamepadConfig.bShouldActivateAutomatically)
	{
		// print CharacterID GEngine
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GamepadConfig - CharacterIndex 0: %d"), CharacterIndex));
		}
		FModifyContextOptions Options = {};
		Options.bIgnoreAllPressedKeysUntilRelease = false;
		// Register gamepad config
		Subsystem->AddPlayerMappableConfig(GamepadConfig.Config.LoadSynchronous(), Options);
	}

	else if (CharacterIndex == 1 && KeyboardConfig.bShouldActivateAutomatically)
	{
		// print CharacterID GEngine
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("KeyboardConfig - CharacterIndex 1: %d"), CharacterIndex));
		}
		FModifyContextOptions Options = {};
		Options.bIgnoreAllPressedKeysUntilRelease = false;
		// Register keyboard config
		Subsystem->AddPlayerMappableConfig(KeyboardConfig.Config.LoadSynchronous(), Options);
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &UBTPlayerInput::RequestStartMovement);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Completed, this, &UBTPlayerInput::RequestCancelMovement);
	EnhancedInputComponent->BindAction(LeftLightInputAction, ETriggerEvent::Started, this, &UBTPlayerInput::RequestLeftLightAction);
	EnhancedInputComponent->BindAction(LeftHeavyInputAction, ETriggerEvent::Started, this, &UBTPlayerInput::RequestLeftHeavyAction);
	EnhancedInputComponent->BindAction(RightLightInputAction, ETriggerEvent::Started, this, &UBTPlayerInput::RequestRightLightAction);
	EnhancedInputComponent->BindAction(RightHeavyInputAction, ETriggerEvent::Started, this, &UBTPlayerInput::RequestRightHeavyAction);
	EnhancedInputComponent->BindAction(SprawlInputAction, ETriggerEvent::Started, this, &UBTPlayerInput::RequestSprawlAction);
}

void UBTPlayerInput::RequestStartMovement(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const ABTGameState* GameState = UBTGameFunctionLibrary::GetBTGameState(this);
	if (PlayerCharacter && GameState && GameState->GetGameState() == EGameState::InGame)
	{
		PlayerCharacter->AddMovementBuffer(MovementVector);
	}
}

void UBTPlayerInput::RequestCancelMovement(const FInputActionValue& Value)
{
	const ABTGameState* GameState = UBTGameFunctionLibrary::GetBTGameState(this);
	if (PlayerCharacter && GameState && GameState->GetGameState() == EGameState::InGame)
	{
		PlayerCharacter->RefreshMovementBuffer();
	}
}

void UBTPlayerInput::RequestLeftLightAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::LeftLight);
	}
}

void UBTPlayerInput::RequestLeftHeavyAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::LeftHeavy);
	}
}

void UBTPlayerInput::RequestRightLightAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::RightLight);
	}
}

void UBTPlayerInput::RequestRightHeavyAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::RightHeavy);
	}
}

void UBTPlayerInput::RequestSprawlAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::Sprawl);
	}
}

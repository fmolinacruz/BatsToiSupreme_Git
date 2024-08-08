// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommon/BTLocalPlayerInput.h"

#include "GameModes/BTGameState.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerMappableInputConfig.h"

#include "Characters/BTPlayerCharacter.h"
#include "PlayerCommon/BTPlayerController.h"

#include "Utilities/BTGameFunctionLibrary.h"


// Sets default values for this component's properties
UBTLocalPlayerInput::UBTLocalPlayerInput()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UBTLocalPlayerInput::BeginPlay()
{
	Super::BeginPlay();
}

void UBTLocalPlayerInput::InitializeInputComponent(UInputComponent* PlayerInputComponent)
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

	// Register any default input configs
	for (const FMappableConfig& InputConfig : DefaultInputConfigs)
	{
		if (InputConfig.bShouldActivateAutomatically)
		{
			FModifyContextOptions Options = {};
			Options.bIgnoreAllPressedKeysUntilRelease = false;

			Subsystem->AddPlayerMappableConfig(InputConfig.Config.LoadSynchronous(), Options);
		}
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &UBTLocalPlayerInput::RequestStartMovement);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Completed, this, &UBTLocalPlayerInput::RequestCancelMovement);
	EnhancedInputComponent->BindAction(LeftLightInputAction, ETriggerEvent::Started, this, &UBTLocalPlayerInput::RequestLeftLightAction);
	EnhancedInputComponent->BindAction(LeftHeavyInputAction, ETriggerEvent::Started, this, &UBTLocalPlayerInput::RequestLeftHeavyAction);
	EnhancedInputComponent->BindAction(RightLightInputAction, ETriggerEvent::Started, this, &UBTLocalPlayerInput::RequestRightLightAction);
	EnhancedInputComponent->BindAction(RightHeavyInputAction, ETriggerEvent::Started, this, &UBTLocalPlayerInput::RequestRightHeavyAction);
	EnhancedInputComponent->BindAction(SprawlInputAction, ETriggerEvent::Started, this, &UBTLocalPlayerInput::RequestSprawlAction);
}

void UBTLocalPlayerInput::RequestStartMovement(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const ABTGameState* GameState = UBTGameFunctionLibrary::GetBTGameState(this);
	if (PlayerCharacter && GameState && GameState->GetGameState() == EGameState::InGame)
	{
		PlayerCharacter->AddMovementBuffer(MovementVector);
	}
}

void UBTLocalPlayerInput::RequestCancelMovement(const FInputActionValue& Value)
{
	const ABTGameState* GameState = UBTGameFunctionLibrary::GetBTGameState(this);
	if (PlayerCharacter && GameState && GameState->GetGameState() == EGameState::InGame)
	{
		PlayerCharacter->RefreshMovementBuffer();
	}
}

void UBTLocalPlayerInput::RequestLeftLightAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::LeftLight);
	}
}

void UBTLocalPlayerInput::RequestLeftHeavyAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::LeftHeavy);
	}
}

void UBTLocalPlayerInput::RequestRightLightAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::RightLight);
	}
}

void UBTLocalPlayerInput::RequestRightHeavyAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::RightHeavy);
	}
}

void UBTLocalPlayerInput::RequestSprawlAction(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->HandleTriggerAbilityInput(EAbilityInputType::Sprawl);
	}
}

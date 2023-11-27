// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCommon/BTPlayerInput.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerMappableInputConfig.h"
#include "Characters/BTPlayerCharacter.h"
#include "PlayerCommon/BTPlayerController.h"

UBTPlayerInput::UBTPlayerInput()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBTPlayerInput::BeginPlay()
{
	Super::BeginPlay();
}

void UBTPlayerInput::InitializeInputComponent(UInputComponent* PlayerInputComponent)
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
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &UBTPlayerInput::RequestMove);
}

void UBTPlayerInput::RequestMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (PlayerCharacter)
	{
		PlayerCharacter->MoveCharacter(MovementVector);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommon/BTUISelectInput.h"

#include "PlayerCommon/BTPlayerController.h"
#include "Input/BTInputReceiver.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerMappableInputConfig.h"

// Sets default values for this component's properties
UBTUISelectInput::UBTUISelectInput()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBTUISelectInput::BeginPlay()
{
	Super::BeginPlay();
}

void UBTUISelectInput::InitializeInputComponent(UInputComponent* PlayerInputComponent, int CharacterIndex)
{
	if (!PlayerInputComponent)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InitializeInputComponent"));
		}
		return;
	}

	ABTInputReceiver* OwningInputReceiver = Cast<ABTInputReceiver>(GetOwner());
	if (!OwningInputReceiver)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OwningInputReceiver is nullptr"));
		}
		return;
	}

	// Get the player controller from AInputReceive
	ABTPlayerController* PC = Cast<ABTPlayerController>(OwningInputReceiver->GetController());
	if (!PC)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerController old is nullptr"));
		}
		return;
	}

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	if (!LP)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LocalPlayer is nullptr"));
		}
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Subsystem is nullptr"));
		}
		return;
	}

	//// Register any default input configs
	//for (const FMappableConfig& InputConfig : MappableInputConfigs)
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

	// Cast the PlayerInputComponent to UEnhancedInputComponent and bind actions
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Started, this, &UBTUISelectInput::OnSelect);
		EnhancedInputComponent->BindAction(SelectInputActionKB, ETriggerEvent::Started, this, &UBTUISelectInput::OnSelect);
		EnhancedInputComponent->BindAction(MenuLeftInputAction, ETriggerEvent::Started, this, &UBTUISelectInput::OnMenuLeft);
		EnhancedInputComponent->BindAction(MenuLeftInputActionKB, ETriggerEvent::Started, this, &UBTUISelectInput::OnMenuLeft);
		EnhancedInputComponent->BindAction(MenuRightInputAction, ETriggerEvent::Started, this, &UBTUISelectInput::OnMenuRight);
		EnhancedInputComponent->BindAction(MenuRightInputActionKB, ETriggerEvent::Started, this, &UBTUISelectInput::OnMenuRight);
		EnhancedInputComponent->BindAction(RestoreInputAction, ETriggerEvent::Started, this, &UBTUISelectInput::Restore);
		EnhancedInputComponent->BindAction(RestoreInputActionKB, ETriggerEvent::Started, this, &UBTUISelectInput::Restore);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnhancedInputComponent is nullptr"));
		}
	}
}

void UBTUISelectInput::InitializeWithInputReceiver(ABTInputReceiver* NewInputReceiver)
{
	if (!NewInputReceiver)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NewInputReceiver is nullptr"));
		}
		return;
	}
	InputReceiver = NewInputReceiver;
}

void UBTUISelectInput::OnSelect(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnSelect"));
	}

	if (!InputReceiver)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InputReceiver is nullptr"));
		}
		return;
	}
	InputReceiver->OnCharacterSelected();
}

void UBTUISelectInput::OnMenuLeft(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnMenuLeft"));
	}

	if (!InputReceiver)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InputReceiver is nullptr"));
		}
		return;
	}
	InputReceiver->OnMenuLeft();
}

void UBTUISelectInput::OnMenuRight(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnMenuRight"));
	}

	if (!InputReceiver)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InputReceiver is nullptr"));
		}
		return;
	}
	InputReceiver->OnMenuRight();
}

void UBTUISelectInput::Restore(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnRestore"));
	}

	if (!InputReceiver)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InputReceiver is nullptr"));
		}
		return;
	}
	InputReceiver->OnRestore();
}

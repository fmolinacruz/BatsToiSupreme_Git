// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommon/BTLocalUISelectInput.h"

#include "PlayerCommon/BTLocalPlayerController.h"
#include "Input/BTLocalInputReceiver.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerMappableInputConfig.h"

// Sets default values for this component's properties
UBTLocalUISelectInput::UBTLocalUISelectInput()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBTLocalUISelectInput::BeginPlay()
{
	Super::BeginPlay();
}

void UBTLocalUISelectInput::InitializeInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InitializeInputComponent"));
		}
		return;
	}

	ABTLocalInputReceiver* OwningInputReceiver = Cast<ABTLocalInputReceiver>(GetOwner());
	if (!OwningInputReceiver)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OwningInputReceiver is nullptr"));
		}
		return;
	}

	// Get the player controller from AInputReceive
	ABTLocalPlayerController* PC = Cast<ABTLocalPlayerController>(OwningInputReceiver->GetController());
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

	// Register any default input configs
	for (const FLocalMappableConfig& InputConfig : MappableInputConfigs)
	{
		if (InputConfig.bShouldActivateAutomatically)
		{
			FModifyContextOptions Options = {};
			Options.bIgnoreAllPressedKeysUntilRelease = false;

			Subsystem->AddPlayerMappableConfig(InputConfig.Config.LoadSynchronous(), Options);
		}
	}

	// Cast the PlayerInputComponent to UEnhancedInputComponent and bind actions
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Started, this, &UBTLocalUISelectInput::OnSelect);
		EnhancedInputComponent->BindAction(SelectInputActionKB, ETriggerEvent::Started, this, &UBTLocalUISelectInput::OnSelect);
		EnhancedInputComponent->BindAction(MenuLeftInputAction, ETriggerEvent::Started, this, &UBTLocalUISelectInput::OnMenuLeft);
		EnhancedInputComponent->BindAction(MenuLeftInputActionKB, ETriggerEvent::Started, this, &UBTLocalUISelectInput::OnMenuLeft);
		EnhancedInputComponent->BindAction(MenuRightInputAction, ETriggerEvent::Started, this, &UBTLocalUISelectInput::OnMenuRight);
		EnhancedInputComponent->BindAction(MenuRightInputActionKB, ETriggerEvent::Started, this, &UBTLocalUISelectInput::OnMenuRight);
		EnhancedInputComponent->BindAction(RestoreInputAction, ETriggerEvent::Started, this, &UBTLocalUISelectInput::Restore);
		EnhancedInputComponent->BindAction(RestoreInputActionKB, ETriggerEvent::Started, this, &UBTLocalUISelectInput::Restore);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnhancedInputComponent is nullptr"));
		}
	}
}

void UBTLocalUISelectInput::InitializeWithInputReceiver(ABTLocalInputReceiver* NewInputReceiver)
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

void UBTLocalUISelectInput::OnSelect(const FInputActionValue& Value)
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

void UBTLocalUISelectInput::OnMenuLeft(const FInputActionValue& Value)
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

void UBTLocalUISelectInput::OnMenuRight(const FInputActionValue& Value)
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

void UBTLocalUISelectInput::Restore(const FInputActionValue& Value)
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


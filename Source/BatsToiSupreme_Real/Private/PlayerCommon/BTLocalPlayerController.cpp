// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCommon/BTLocalPlayerController.h"
#include "Menu/WBTMenu.h"
#include "Utilities/BTLogging.h"
#include "PlayerCommon/BTPlayerInput.h"
#include "Characters/BTPlayerCharacter.h"


ABTLocalPlayerController::ABTLocalPlayerController()
	: bHasSetupInput(false)
{
	bAutoManageActiveCameraTarget = false;
}

UWBTMenu* ABTLocalPlayerController::CreateMenuWidget()
{
	if (IsLocalPlayerController() && MenuUIClass)
	{
		CharacterSelectionWidgetRef = CreateWidget<UWBTMenu>(this, MenuUIClass);
		if (CharacterSelectionWidgetRef)
		{
			CharacterSelectionWidgetRef->AddToViewport();
			return CharacterSelectionWidgetRef;
		}
	}
	return nullptr;
}

void ABTLocalPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABTLocalPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);

	BTLOG_DISPLAY("[ABTPlayerController] - AcknowledgePossession: Posses %s", *InPawn->GetName());
	if (bHasSetupInput)
	{
		return;
	}

	PlayerCharacter = Cast<ABTPlayerCharacter>(GetCharacter());
	if (PlayerCharacter)
	{
		PlayerCharacter->GetBTInputComponent()->InitializeInputComponent(InputComponent);
		bHasSetupInput = true;
	}
	//else
	//{
	//	// BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter!");
	//	InputReceiver = Cast<ABTInputReceiver>(InPawn);
	//	if (InputReceiver)
	//	{
	//		UBTUISelectInput* SelectionInputComponent = InputReceiver->GetBTUISelectionInputComponent();
	//		if (SelectionInputComponent)
	//		{
	//			SelectionInputComponent->InitializeWithInputReceiver(InputReceiver);
	//			SelectionInputComponent->InitializeInputComponent(InputComponent);
	//		}
	//	}
	//	else
	//	{
	//		BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter or ABTInputReceiver!");
	//	}
	//}
}

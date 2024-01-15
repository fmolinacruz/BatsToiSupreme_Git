// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCommon/BTPlayerController.h"

#include "Input/BTInputReceiver.h"
#include "PlayerCommon/BTUISelectInput.h"

#include "Characters/BTPlayerCharacter.h"
#include "PlayerCommon/BTPlayerInput.h"
#include "Utilities/BTLogging.h"

//#include "Blueprint/UserWidget.h"
#include "Menu/WBTMenu.h"

ABTPlayerController::ABTPlayerController() : bHasSetupInput(false)
{
	bAutoManageActiveCameraTarget = false;
}

void ABTPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

UWBTMenu* ABTPlayerController::CreateMenuWidget()
{
	if (IsLocalPlayerController() && MenuUIClass)
	{
		UWBTMenu* MyCharacterSelectUI = CreateWidget<UWBTMenu>(this, MenuUIClass);
		if (MyCharacterSelectUI)
		{
			MyCharacterSelectUI->AddToViewport();
			return MyCharacterSelectUI;
		}
	}
	return nullptr;
}

void ABTPlayerController::AcknowledgePossession(APawn* InPawn)
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
	else
	{
		//BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter!");
		InputReceiver = Cast<ABTInputReceiver>(InPawn);
		if (InputReceiver)
		{
			UBTUISelectInput* SelectionInputComponent = InputReceiver->GetBTUISelectionInputComponent();
			if (SelectionInputComponent)
			{
				SelectionInputComponent->InitializeWithInputReceiver(InputReceiver);
				SelectionInputComponent->InitializeInputComponent(InputComponent);
			}
		}
		else
		{
			BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter or ABTInputReceiver!");
		}
	}	
}


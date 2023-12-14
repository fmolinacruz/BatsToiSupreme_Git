// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCommon/BTPlayerController.h"

#include "Characters/BTPlayerCharacter.h"
#include "PlayerCommon/BTPlayerInput.h"
#include "Utilities/BTLogging.h"

ABTPlayerController::ABTPlayerController() : bHasSetupInput(false)
{
}

void ABTPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);

	if (bHasSetupInput)
	{
		return;
	}
	
	PlayerCharacter = Cast<ABTPlayerCharacter>(GetCharacter());
	if (PlayerCharacter)
	{
		PlayerCharacter->GetBTInputComponent()->InitializeInputComponent(InputComponent);
	}
	else
	{
		BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter!");
	}
	bHasSetupInput = true;
}


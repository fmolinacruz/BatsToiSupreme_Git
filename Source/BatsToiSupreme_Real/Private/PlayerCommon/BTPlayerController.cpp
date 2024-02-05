// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCommon/BTPlayerController.h"

#include "Input/BTInputReceiver.h"
#include "PlayerCommon/BTUISelectInput.h"

#include "Characters/BTPlayerCharacter.h"
#include "PlayerCommon/BTPlayerInput.h"
#include "Utilities/BTLogging.h"

//#include "Blueprint/UserWidget.h"
#include "Menu/WBTMenu.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"

ABTPlayerController::ABTPlayerController()
	: bHasSetupInput(false)
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
		CharacterSelectionWidgetRef = CreateWidget<UWBTMenu>(this, MenuUIClass);
		if (CharacterSelectionWidgetRef)
		{
			CharacterSelectionWidgetRef->AddToViewport();
			return CharacterSelectionWidgetRef;
		}
	}
	return nullptr;
}

//Client Only
void ABTPlayerController::TurnOffMenuWidget()
{
	bool IsClient = GetWorld()->IsClient();
	if (!IsClient)
		return;

	if (CharacterSelectionWidgetRef)
	{
		CharacterSelectionWidgetRef->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABTPlayerController::PlayCharacterSelectedAnimation_Implementation(const int PlayerIndex)
{
	if (CharacterSelectionWidgetRef && CharacterSelectionWidgetRef->CharacterAnimationsCPP.IsValidIndex(PlayerIndex))
	{
		UWidgetAnimation* AnimationToPlay = CharacterSelectionWidgetRef->CharacterAnimationsCPP[PlayerIndex];
		if (AnimationToPlay)
		{
			CharacterSelectionWidgetRef->PlayAnimation(AnimationToPlay, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
		}
	}
}

void ABTPlayerController::PlayCharacterDecidedAnimation_Implementation(const int PlayerIndex)
{
	if (CharacterSelectionWidgetRef && CharacterSelectionWidgetRef->CharacterSelectedAnimationsCPP.IsValidIndex(PlayerIndex))
	{
		UWidgetAnimation* AnimationToPlay = CharacterSelectionWidgetRef->CharacterSelectedAnimationsCPP[PlayerIndex];
		if (AnimationToPlay)
		{
			CharacterSelectionWidgetRef->PlayAnimation(AnimationToPlay, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
		}
	}
}

void ABTPlayerController::PlayCharacterRestore_Implementation(const int PlayerIndex)
{
	if (CharacterSelectionWidgetRef && CharacterSelectionWidgetRef->CharacterSelectedAnimationsCPP.IsValidIndex(PlayerIndex))
	{
		UWidgetAnimation* AnimationToPlay = CharacterSelectionWidgetRef->CharacterSelectedAnimationsCPP[PlayerIndex];
		if (AnimationToPlay)
		{
			CharacterSelectionWidgetRef->PlayAnimation(AnimationToPlay, 1.0f, 1, EUMGSequencePlayMode::Reverse, 5.0f);
		}
	}
}

void ABTPlayerController::ChangeCharacterSelectionTexture_Implementation(const int PlayerIndex, const int CharacterChoice)
{
	if (CharacterSelectionWidgetRef && CharacterSelectionWidgetRef->ImagesSourcecCPP.IsValidIndex(CharacterChoice))
	{
		UTexture2D* SelectedTexture = CharacterSelectionWidgetRef->ImagesSourcecCPP[CharacterChoice];
		if (SelectedTexture)
		{
			CharacterSelectionWidgetRef->PlayerImagesCPP[PlayerIndex]->SetBrushFromTexture(SelectedTexture, true);
		}
	}
}

//Turn off CharacterSelect Menu when done select character
void ABTPlayerController::Client_TurnOffCharacterSelectMenu_Implementation()
{
	TurnOffMenuWidget();
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
		int CharacterIndex = PlayerCharacter->GetCharacterIndex();
		// print CharacterID GEngine
		//if (GEngine)
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CharacterID: %d"), CharacterIndex));
		//}

		PlayerCharacter->GetBTInputComponent()->InitializeInputComponent(InputComponent, CharacterIndex);
		bHasSetupInput = true;
	}
	else
	{
		// BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter!");
		InputReceiver = Cast<ABTInputReceiver>(InPawn);
		if (InputReceiver)
		{
			int IRCharacterIndex = InputReceiver->GetIRCharacterIndex();
			UBTUISelectInput* SelectionInputComponent = InputReceiver->GetBTUISelectionInputComponent();
			if (SelectionInputComponent)
			{
				SelectionInputComponent->InitializeWithInputReceiver(InputReceiver);
				SelectionInputComponent->InitializeInputComponent(InputComponent, IRCharacterIndex);
			}
		}
		else
		{
			BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter or ABTInputReceiver!");
		}
	}
}


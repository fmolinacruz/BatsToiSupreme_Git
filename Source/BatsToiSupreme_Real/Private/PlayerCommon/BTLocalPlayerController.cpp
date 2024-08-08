// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCommon/BTLocalPlayerController.h"
#include "Menu/WBTMenu.h"
#include "Utilities/BTLogging.h"
#include "PlayerCommon/BTLocalPlayerInput.h"
#include "Characters/BTLocalPlayerCharacter.h"
#include "Input/BTLocalInputReceiver.h"
#include "PlayerCommon/BTLocalUISelectInput.h"
#include "GameModes/BTLocalOfflineGameMode.h"
#include "Kismet/GameplayStatics.h"


ABTLocalPlayerController::ABTLocalPlayerController()
	: bHasSetupInput(false)
{
	bAutoManageActiveCameraTarget = false;
}

void ABTLocalPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

//UWBTMenu* ABTLocalPlayerController::CreateMenuWidget()
//{
//	if (IsLocalPlayerController() && MenuUIClass)
//	{
//		CharacterSelectionWidgetRef = CreateWidget<UWBTMenu>(this, MenuUIClass);
//		if (CharacterSelectionWidgetRef)
//		{
//			CharacterSelectionWidgetRef->AddToViewport();
//			return CharacterSelectionWidgetRef;
//		}
//	}
//	return nullptr;
//}

UWBTMenu* ABTLocalPlayerController::GetMenuWidgetFromGameMode()
{
	ABTLocalOfflineGameMode* GameMode = GetGameMode();
	if (GameMode)
	{
		CharacterSelectionWidgetRef = GameMode->GetMenuWidgetRef();
	}
	return CharacterSelectionWidgetRef;
}

void ABTLocalPlayerController::PlayCharacterSelectedAnimation(const int PlayerIndex)
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

void ABTLocalPlayerController::PlayCharacterDecidedAnimation(const int PlayerIndex)
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

void ABTLocalPlayerController::PlayCharacterRestore(const int PlayerIndex)
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

void ABTLocalPlayerController::ChangeCharacterSelectionTexture(const int PlayerIndex, const int CharacterChoice)
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

void ABTLocalPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);

	BTLOG_DISPLAY("[ABTPlayerController] - AcknowledgePossession: Posses %s", *InPawn->GetName());
	if (bHasSetupInput)
	{
		return;
	}

	PlayerCharacter = Cast<ABTLocalPlayerCharacter>(GetCharacter());
	if (PlayerCharacter)
	{
		PlayerCharacter->GetBTLocalInputComponent()->InitializeInputComponent(InputComponent);
		bHasSetupInput = true;
	}
	else
	{
		// BTLOG_WARNING("This controller is not attached to a ABTPlayerCharacter!");
		InputReceiver = Cast<ABTLocalInputReceiver>(InPawn);
		if (InputReceiver)
		{
			UBTLocalUISelectInput* SelectionInputComponent = InputReceiver->GetBTUISelectionInputComponent();
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

ABTLocalOfflineGameMode* ABTLocalPlayerController::GetGameMode() const
{
	return Cast<ABTLocalOfflineGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

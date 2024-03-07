// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/BTInputReceiver.h"

#include "PlayerCommon/BTPlayerController.h"
#include "PlayerCommon/BTUISelectInput.h"
#include "GameModes/BTGameModeBase.h"
#include "Menu/WBTMenu.h"
#include "Menu/WBTCharacterSelect.h"
#include "Net/UnrealNetwork.h"
#include "Utilities/BTLogging.h"

// Sets default values
ABTInputReceiver::ABTInputReceiver()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	BTUISelectionInputComponent = CreateDefaultSubobject<UBTUISelectInput>(TEXT("InputComponent"));
}

void ABTInputReceiver::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABTInputReceiver, CurrentPlayerIndex);
	DOREPLIFETIME(ABTInputReceiver, CurrentPlayerController);
	DOREPLIFETIME(ABTInputReceiver, OtherPlayerController);
	DOREPLIFETIME(ABTInputReceiver, MenuWidgetRefCPP);
	DOREPLIFETIME(ABTInputReceiver, CharacterMenuRefCPP);
	DOREPLIFETIME(ABTInputReceiver, MyIRCharacterIndexCPP);
}

void ABTInputReceiver::BeginPlay()
{
	Super::BeginPlay();

	CreateMenuUI();
}

void ABTInputReceiver::CreateMenuUI()
{
	if (CurrentPlayerController)
	{
		MenuWidgetRefCPP = CurrentPlayerController->CreateMenuWidget();

		// MenuWidgetRefCPP is nullptr;
		if (!MenuWidgetRefCPP)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MyMenuWidget is nullptr"));
			}
		}
	}
}

void ABTInputReceiver::InitializeWithPlayerController(ABTPlayerController* NewPlayerController, int32 PlayerIndex)
{
	if (!NewPlayerController)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NewPlayerController is nullptr"));
		}
		return;
	}
	CurrentPlayerController = NewPlayerController;
	CurrentPlayerIndex = PlayerIndex;
}

void ABTInputReceiver::OnCharacterSelected()
{
	if (CharacterMenuRefCPP == nullptr)
	{
		Server_CharacterSelected();
		if (!MenuWidgetRefCPP)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MenuWidgetRefCPP is nullptr"));
			}
			return;
		}
		CharacterMenuRefCPP = MenuWidgetRefCPP->AddCharacterSelect(CurrentPlayerIndex);
	}
	else
	{
		if (IsReady == false)
		{
			IsReady = true;
			const int32 CharacterChoice = CharacterMenuRefCPP->CharacterChoice;
			Server_CharacterDecided(CharacterChoice);
		}
		//MenuWidgetRefCPP->CharacterSelect->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABTInputReceiver::OnMenuLeft()
{
	if (IsReady == false)
	{
		if (!CharacterMenuRefCPP)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CharacterMenuRefCPP is nullptr"));
			}
			return;
		}
		const int32 CharacterChoice = CharacterMenuRefCPP->SwitchCharacter(-1);

		// Real UI update
		Server_CharacterChoiceChanged(CharacterChoice);
	}
}

void ABTInputReceiver::OnMenuRight()
{
	if (IsReady == false)
	{
		if (!CharacterMenuRefCPP)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CharacterMenuRefCPP is nullptr"));
			}
			return;
		}
		const int32 CharacterChoice = CharacterMenuRefCPP->SwitchCharacter(1);

		// Real UI update
		Server_CharacterChoiceChanged(CharacterChoice);
	}
}

void ABTInputReceiver::OnRestore()
{
	if (IsReady == true)
	{
		IsReady = false;

		if (!CharacterMenuRefCPP)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CharacterMenuRefCPP is nullptr"));
			}
			return;
		}
		Server_CharacterRestore();
	}
}

void ABTInputReceiver::Server_CharacterSelected_Implementation()
{
	CurrentPlayerController->PlayCharacterSelectedAnimation(CurrentPlayerIndex);
	
	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->PlayCharacterSelectedAnimation(CurrentPlayerIndex);
	}
}

void ABTInputReceiver::Server_CharacterDecided_Implementation(int32 CharacterChoice)
{
	CurrentPlayerController->PlayCharacterDecidedAnimation(CurrentPlayerIndex);

	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->PlayCharacterDecidedAnimation(CurrentPlayerIndex);
	}

	ABTGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABTGameModeBase>();
	if (!GameMode)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameMode is nullptr"));
		}
		return;
	}
	if (bHasSpawnedPlayer)
	{
		return;
	}
	GameMode->CheckForSpawningPlayerCharacter(CurrentPlayerController, CharacterChoice, CurrentPlayerIndex);
	bHasSpawnedPlayer = true;
}

void ABTInputReceiver::Server_CharacterRestore_Implementation()
{
	CurrentPlayerController->PlayCharacterRestore(CurrentPlayerIndex);

	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->PlayCharacterRestore(CurrentPlayerIndex);
	}

	ABTGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABTGameModeBase>();
	if (!GameMode)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameMode is nullptr"));
		}
		return;
	}
	GameMode->RestorePlayerCharacter(CurrentPlayerIndex);
	bHasSpawnedPlayer = false;
}

void ABTInputReceiver::Server_CharacterChoiceChanged_Implementation(int32 CharacterChoice)
{
	CurrentPlayerController->ChangeCharacterSelectionTexture(CurrentPlayerIndex, CharacterChoice);

	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->ChangeCharacterSelectionTexture(CurrentPlayerIndex, CharacterChoice);
	}
}

void ABTInputReceiver::Multicast_CharacterSelected_Implementation()
{
	/*
	if (MenuWidgetRefCPP && MenuWidgetRefCPP->CharacterAnimationsCPP.IsValidIndex(CurrentPlayerIndex))
	{
		UWidgetAnimation* AnimationToPlay = MenuWidgetRefCPP->CharacterAnimationsCPP[CurrentPlayerIndex];
		if (AnimationToPlay)
		{
			MenuWidgetRefCPP->PlayAnimation(AnimationToPlay, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
		}
	}
	*/
}

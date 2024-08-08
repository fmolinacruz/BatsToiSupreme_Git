// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/BTLocalInputReceiver.h"

#include "PlayerCommon/BTLocalPlayerController.h"
#include "PlayerCommon/BTLocalUISelectInput.h"
#include "GameModes/BTLocalOfflineGameMode.h"
#include "Menu/WBTMenu.h"
#include "Menu/WBTCharacterSelect.h"
#include "Utilities/BTLogging.h"


// Sets default values
ABTLocalInputReceiver::ABTLocalInputReceiver()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BTUISelectionInputComponent = CreateDefaultSubobject<UBTLocalUISelectInput>(TEXT("InputComponent"));
}

// Called when the game starts or when spawned
void ABTLocalInputReceiver::BeginPlay()
{
	Super::BeginPlay();

	CreateMenuUI();
}

void ABTLocalInputReceiver::CreateMenuUI()
{
	if (CurrentPlayerController)
	{
		MenuWidgetRefCPP = CurrentPlayerController->GetMenuWidgetFromGameMode();

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

void ABTLocalInputReceiver::InitializeWithPlayerController(ABTLocalPlayerController* NewPlayerController, int32 PlayerIndex)
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

void ABTLocalInputReceiver::OnCharacterSelected()
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
		// MenuWidgetRefCPP->CharacterSelect->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABTLocalInputReceiver::OnMenuLeft()
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

void ABTLocalInputReceiver::OnMenuRight()
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

void ABTLocalInputReceiver::OnRestore()
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

void ABTLocalInputReceiver::SetMenuWidget(UWBTMenu* MenuWidget)
{
	MenuWidgetRefCPP = MenuWidget;
}

void ABTLocalInputReceiver::Server_CharacterSelected()
{
	BTLOG_DISPLAY("[ABTInputReceiver] - Server_CharacterSelected_Implementation");
	CurrentPlayerController->PlayCharacterSelectedAnimation(CurrentPlayerIndex);

	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->PlayCharacterSelectedAnimation(CurrentPlayerIndex);
	}
}

void ABTLocalInputReceiver::Server_CharacterDecided(int32 CharacterChoice)
{
	BTLOG_DISPLAY("[ABTInputReceiver] - Server_CharacterDecided_Implementation");
	CurrentPlayerController->PlayCharacterDecidedAnimation(CurrentPlayerIndex);

	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->PlayCharacterDecidedAnimation(CurrentPlayerIndex);
	}

	ABTLocalOfflineGameMode* GameMode = GetWorld()->GetAuthGameMode<ABTLocalOfflineGameMode>();
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

void ABTLocalInputReceiver::Server_CharacterRestore()
{
	CurrentPlayerController->PlayCharacterRestore(CurrentPlayerIndex);

	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->PlayCharacterRestore(CurrentPlayerIndex);
	}

	ABTLocalOfflineGameMode* GameMode = GetWorld()->GetAuthGameMode<ABTLocalOfflineGameMode>();
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

void ABTLocalInputReceiver::Server_CharacterChoiceChanged(int32 CharacterChoice)
{
	CurrentPlayerController->ChangeCharacterSelectionTexture(CurrentPlayerIndex, CharacterChoice);

	// Update UI of other clients
	if (OtherPlayerController)
	{
		OtherPlayerController->ChangeCharacterSelectionTexture(CurrentPlayerIndex, CharacterChoice);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/BTInputReceiver.h"

#include "PlayerCommon/BTPlayerController.h"
#include "PlayerCommon/BTUISelectInput.h"
#include "Menu/WBTMenu.h"
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
		const UWBTMenu* MenuWidgetRefCPP = CurrentPlayerController->CreateMenuWidget();

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
	Server_CharacterSelected();
}

void ABTInputReceiver::Server_CharacterSelected_Implementation()
{
	CurrentPlayerController->PlayCharacterSelectedAnimation(CurrentPlayerIndex);
	if (OtherPlayerController)
	{
		// Update UI of other clients
		OtherPlayerController->PlayCharacterSelectedAnimation(CurrentPlayerIndex);
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

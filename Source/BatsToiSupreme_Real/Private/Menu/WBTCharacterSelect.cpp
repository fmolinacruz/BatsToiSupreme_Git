// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/WBTCharacterSelect.h"
#include "Menu/WBTMenu.h"
#include "PlayerCommon/BTPlayerController.h"

void UWBTCharacterSelect::NativeConstruct()
{
	Super::NativeConstruct();

	// Initialize PlayerColors with your desired colors
	PlayerColors = {
		FLinearColor(1.0f, 0.243137f, 0.0f, 1.0f), // Orange
		FLinearColor(1.0f, 0.243137f, 1.0f, 1.0f)  // Purple
	};

	if (!PlayerColor)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("[UBT_WBP_CharacterSelect] - NativeConstruct: PlayerColor NULL!"));
		}
		return;
	}

	// Check if MyBorder is valid before attempting to use it
	if (PlayerColor)
	{
		PlayerColor->SetBrushColor(PlayerColors[CharacterChoice]);
	}

	// Check if MyTextBlock is valid before attempting to use it
	if (PlayerNumber)
	{
		FText PlayerNumberText = FText::FromString("P" + (CharacterChoice + 1));
		PlayerNumber->SetText(PlayerNumberText);
	}
}

int32 UWBTCharacterSelect::SwitchCharacter(const int32 Direction)
{
	// length MainMenu->ImagesSourcecCPP
	const int32 Length = MainMenu->ImagesSourcecCPP.Num();
	if (CharacterChoice + Direction >= Length)
	{
		CharacterChoice = 0;
	}
	else
	{
		if (CharacterChoice + Direction < 0)
		{
			CharacterChoice = Length - 1;
		}
		else
		{
			CharacterChoice += Direction;
		}
	}

	return CharacterChoice;
}

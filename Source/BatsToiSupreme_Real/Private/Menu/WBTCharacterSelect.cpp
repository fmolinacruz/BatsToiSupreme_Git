// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/WBTCharacterSelect.h"
#include "Menu/WBTMenu.h"

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
		FText playerNumerText = FText::FromString("P" + (CharacterChoice + 1));
		PlayerNumber->SetText(playerNumerText);
	}
}

void UWBTCharacterSelect::SwitchCharacter(int32 Direction)
{
	// length MainMenu->ImagesSourcecCPP
	int32 length = MainMenu->ImagesSourcecCPP.Num();
	if (CharacterChoice + Direction >= length)
	{
		CharacterChoice = 0;
	}
	else
	{
		if (CharacterChoice + Direction < 0)
		{
			CharacterChoice = length - 1;
		}
		else
		{
			CharacterChoice += Direction;
		}
	}

	if (MainMenu->ImagesSourcecCPP.IsValidIndex(CharacterChoice))
	{
		UTexture2D* SelectedTexture = MainMenu->ImagesSourcecCPP[CharacterChoice];
		if (SelectedTexture)
		{
			MainMenu->PlayerImagesCPP[PlayerIndex]->SetBrushFromTexture(SelectedTexture, true);
		}
	}
}

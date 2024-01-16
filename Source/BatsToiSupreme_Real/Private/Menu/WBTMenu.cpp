// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/WBTMenu.h"
#include "Menu/WBTCharacterSelect.h"


void UWBTMenu::NativeConstruct()
{
	Super::NativeConstruct();

	AddToImagesSourcec();
}

UWBTCharacterSelect* UWBTMenu::AddCharacterSelect(int32 PlayerIndex)
{
	if (!CharacterSelectMenuTemplate)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CharacterSelectMenuTemplate is null"));
		}
		return nullptr;
	}
	UWBTCharacterSelect* CharacterSelectMenu = CreateWidget<UWBTCharacterSelect>(GetWorld(), CharacterSelectMenuTemplate);
	CharacterSelectMenu->CharacterChoice = PlayerIndex;
	CharacterSelectMenu->PlayerIndex = PlayerIndex;
	CharacterSelectMenu->MainMenu= this;
	return CharacterSelectMenu;
}

void UWBTMenu::AddToImagesSourcec()
{
	if (CharacterIn1)
	{
		CharacterAnimationsCPP.Add(CharacterIn1);
	}
	if (CharacterIn2)
	{
		CharacterAnimationsCPP.Add(CharacterIn2);
	}

	if (PlayerImage1)
	{
		PlayerImagesCPP.Add(PlayerImage1);
	}
	if (PlayerImage2)
	{
		PlayerImagesCPP.Add(PlayerImage2);
	}

	if (Image1)
	{
		ImagesSourcecCPP.Add(Image1);
	}
	if (Image2)
	{
		ImagesSourcecCPP.Add(Image2);
	}
	if (Image3)
	{
		ImagesSourcecCPP.Add(Image3);
	}
	if (Image4)
	{
		ImagesSourcecCPP.Add(Image4);
	}
	if (Image5)
	{
		ImagesSourcecCPP.Add(Image5);
	}
	if (Image6)
	{
		ImagesSourcecCPP.Add(Image6);
	}
	if (Image7)
	{
		ImagesSourcecCPP.Add(Image7);
	}
	if (Image8)
	{
		ImagesSourcecCPP.Add(Image8);
	}
}
